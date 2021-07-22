/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 21:30:38 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 16:44:37 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ret_error(t_all *prm, int error)
{
	(error == ERR_FD) ? ft_putstr_fd("Error\nBad File Descriptor\n", 1) : 0;
	(error == ERR_GNL) ? ft_putstr_fd("Error\nError in GNL\n", 1) : 0;
	(error == ERR_INVALID_RESOL) ?
			ft_putstr_fd("Error\nBad invalid resolution\n", 1) : 0;
	(error == ERR_INVALID_FC) ?
			ft_putstr_fd("Error\nInvalid Floor/Ceil\n", 1) : 0;
	(error == ERR_MALLOC) ? ft_putstr_fd("Error\nMalloc fail\n", 1) : 0;
	(error == ERR_INVALID_TEXTURE) ?
			ft_putstr_fd("Error\nInvalid texture image\n", 1) : 0;
	(error == ERR_INVALID_LINE) ? ft_putstr_fd("Error\nInvalid str\n", 1) : 0;
	(error == ERR_INVALID_MAP) ? ft_putstr_fd("Error\nInvalid map\n", 1) : 0;
	(error == ERR_NO_RESOL) ? ft_putstr_fd("Error\nNo resolution\n", 1) : 0;
	(error == ERR_MISS_TEXTURE) ? ft_putstr_fd("Error\nNo texture\n", 1) : 0;
	(error == ERR_MISS_COLOR_FC) ?
			ft_putstr_fd("Error\nNo Floor/Ceil color\n", 1) : 0;
	(error == ERR_START_POSITION) ?
			ft_putstr_fd("Error\nInvalid position\n", 1) : 0;
	(error == ERR_MAP_NOT_CLOSED) ?
			ft_putstr_fd("Error\nMap is not closed\n", 1) : 0;
	close_prog(prm, error);
	return (0);
}

int		close_prog(t_all *prm, int error)
{
	int	i;

	i = 0;
	while (i < prm->map.y)
		free(prm->map.tab[i++]);
	free(prm->map.tab);
	if (prm->spr)
		free(prm->spr);
	if (prm->tex.ptr_n)
		mlx_destroy_image(prm->mlx.ptr, prm->tex.ptr_n);
	if (prm->tex.ptr_s)
		mlx_destroy_image(prm->mlx.ptr, prm->tex.ptr_s);
	if (prm->tex.ptr_w)
		mlx_destroy_image(prm->mlx.ptr, prm->tex.ptr_w);
	if (prm->tex.ptr_e)
		mlx_destroy_image(prm->mlx.ptr, prm->tex.ptr_e);
	if (prm->tex.ptr_spr)
		mlx_destroy_image(prm->mlx.ptr, prm->tex.ptr_spr);
	if ((prm->key.esc == 1 || error >= 2) && prm->win.ptr)
		mlx_destroy_window(prm->mlx.ptr, prm->win.ptr);
	free(prm->mlx.ptr);
	exit(0);
	return (0);
}
