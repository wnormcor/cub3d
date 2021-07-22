/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 21:29:54 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 16:52:03 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_digits(char *str, int *i)
{
	int	nbr;

	nbr = 0;
	pass_space(str, i);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		nbr = nbr * 10 + (str[*i] - 48);
		(*i)++;
	}
	return (nbr);
}

void	set_resolution(t_all *prm, char *str, int *i)
{
	int x;
	int y;

	mlx_get_screen_size(prm->mlx.ptr, &x, &y);
	(*i)++;
	prm->win.x = get_digits(str, i);
	prm->win.y = get_digits(str, i);
	if (prm->win.x > x)
		prm->win.x = x;
	if (prm->win.y > y)
		prm->win.y = y;
	pass_space(str, i);
	if (prm->win.x <= 0 || prm->win.y <= 0 || str[*i] != '\0')
		ret_error(prm, ERR_INVALID_RESOL);
}

void	set_fc_colors(t_all *prm, char *str, int *i, char type)
{
	int	r;
	int	g;
	int	b;

	(*i)++;
	r = get_digits(str, i);
	(*i)++;
	g = get_digits(str, i);
	(*i)++;
	b = get_digits(str, i);
	pass_space(str, i);
	if (str[*i] != '\0' || r > 255 || g > 255 || b > 255 ||
									r < 0 || g < 0 || b < 0)
		ret_error(prm, ERR_INVALID_FC);
	if (type == 'F')
		prm->tex.f = r * 256 * 256 + g * 256 + b;
	else if (type == 'C')
		prm->tex.c = r * 256 * 256 + g * 256 + b;
}

void	set_player_pos(t_all *prm)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	while (++i < prm->map.y)
	{
		j = -1;
		while (++j < prm->map.x)
		{
			c = prm->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				prm->pos.x = (double)j + 0.5;
				prm->pos.y = (double)i + 0.5;
				prm->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
				prm->dir.x *= (c == 'W') ? -1 : 1;
				prm->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
				prm->dir.y *= (c == 'N') ? -1 : 1;
				prm->map.pos++;
			}
		}
	}
}

void	check_item(t_all *prm)
{
	int		i;
	int		j;
	int		k;

	free(prm->spr);
	if (!(prm->spr = malloc(sizeof(t_spr) * prm->map.spr)))
		ret_error(prm, ERR_MALLOC);
	i = 0;
	j = -1;
	while (++j < prm->map.y)
	{
		k = -1;
		while (++k < prm->map.x)
		{
			if (prm->map.tab[j][k] == '2')
			{
				prm->spr[i].y = (double)j + 0.5;
				prm->spr[i].x = (double)k + 0.5;
				i++;
			}
		}
	}
}
