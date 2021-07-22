/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:28:56 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/26 23:00:49 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		save_header(t_all *prm, int fd)
{
	unsigned char	bit[14];
	int				i;

	i = 0;
	while (i < 14)
		bit[i++] = (unsigned char)(0);
	bit[0] = (unsigned char)(66);
	bit[1] = (unsigned char)(77);
	i = prm->win.x * prm->win.y * 4 + 54;
	bit[2] = (unsigned char)(i % 256);
	bit[3] = (unsigned char)(i / 256 % 256);
	bit[4] = (unsigned char)(i / 256 / 256 % 256);
	bit[5] = (unsigned char)(i / 256 / 256 / 256);
	bit[10] = (unsigned char)(54);
	write(fd, bit, 14);
}

static void		save_info_x(t_all *prm, int fd)
{
	unsigned char	bit[8];
	int				i;

	i = 0;
	while (i < 7)
		bit[i++] = (unsigned char)(0);
	bit[0] = (unsigned char)(40);
	i = prm->win.x;
	bit[4] = (unsigned char)(i % 256);
	bit[5] = (unsigned char)(i / 256 % 256);
	bit[6] = (unsigned char)(i / 256 / 256 % 256);
	bit[7] = (unsigned char)(i / 256 / 256 / 256);
	write(fd, bit, 8);
}

static void		save_info_y(t_all *prm, int fd)
{
	unsigned char	bit[32];
	int				i;

	i = 0;
	while (i < 33)
		bit[i++] = (unsigned char)(0);
	i = prm->win.y;
	bit[0] = (unsigned char)(i % 256);
	bit[1] = (unsigned char)(i / 256 % 256);
	bit[2] = (unsigned char)(i / 256 / 256 % 256);
	bit[3] = (unsigned char)(i / 256 / 256 / 256);
	bit[4] = (unsigned char)(1);
	bit[6] = (unsigned char)(32);
	write(fd, bit, 32);
}

static void		save_data(t_all *prm, int fd)
{
	unsigned char	bit[4];
	int				i;
	int				j;

	i = prm->win.x * (prm->win.y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < prm->win.x)
		{
			bit[0] = (unsigned char)(prm->img.adr[i] % 256);
			bit[1] = (unsigned char)(prm->img.adr[i] / 256 % 256);
			bit[2] = (unsigned char)(prm->img.adr[i] / 256 / 256 % 256);
			bit[3] = (unsigned char)(0);
			write(fd, bit, 4);
			i++;
			j++;
		}
		i -= 2 * prm->win.x;
	}
}

void			save_bmp(t_all *prm)
{
	int	fd;

	make_screen(prm);
	fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	save_header(prm, fd);
	save_info_x(prm, fd);
	save_info_y(prm, fd);
	save_data(prm, fd);
	close(fd);
	close_prog(prm, OK_STATUS);
}
