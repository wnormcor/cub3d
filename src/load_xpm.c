/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 21:30:44 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/26 23:31:14 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_xpm_3(t_all *prm, char *file, char type)
{
	if (type == 'I')
	{
		prm->tex.ptr_spr = mlx_xpm_file_to_image(prm->mlx.ptr, file,
											&prm->tex.width, &prm->tex.height);
		if (prm->tex.ptr_spr == NULL || prm->tex.width != 64 ||
														prm->tex.height != 64)
			ret_error(prm, ERR_INVALID_TEXTURE);
		prm->tex.spr = (unsigned int *)mlx_get_data_addr(prm->tex.ptr_spr,
							&prm->tex.bpp, &prm->tex.size, &prm->tex.endian);
	}
}

static void	load_xpm_2(t_all *prm, char *file, char type)
{
	if (type == 'W')
	{
		prm->tex.ptr_w = mlx_xpm_file_to_image(prm->mlx.ptr, file,
											&prm->tex.width, &prm->tex.height);
		if (prm->tex.ptr_w == NULL || prm->tex.width != 64 ||
														prm->tex.height != 64)
			ret_error(prm, ERR_INVALID_TEXTURE);
		prm->tex.w = (unsigned int *)mlx_get_data_addr(prm->tex.ptr_w,
							&prm->tex.bpp, &prm->tex.size, &prm->tex.endian);
	}
	else if (type == 'E')
	{
		prm->tex.ptr_e = mlx_xpm_file_to_image(prm->mlx.ptr, file,
											&prm->tex.width, &prm->tex.height);
		if (prm->tex.ptr_e == NULL || prm->tex.width != 64 ||
														prm->tex.height != 64)
			ret_error(prm, ERR_INVALID_TEXTURE);
		prm->tex.e = (unsigned int *)mlx_get_data_addr(prm->tex.ptr_e,
							&prm->tex.bpp, &prm->tex.size, &prm->tex.endian);
	}
	else
		load_xpm_3(prm, file, type);
}

void		load_xpm(t_all *prm, char *file, char type)
{
	if (type == 'N')
	{
		prm->tex.ptr_n = mlx_xpm_file_to_image(prm->mlx.ptr, file,
											&prm->tex.width, &prm->tex.height);
		if (prm->tex.ptr_n == NULL || prm->tex.width != 64 ||
														prm->tex.height != 64)
			ret_error(prm, ERR_INVALID_TEXTURE);
		prm->tex.n = (unsigned int *)mlx_get_data_addr(prm->tex.ptr_n,
							&prm->tex.bpp, &prm->tex.size, &prm->tex.endian);
	}
	else if (type == 'S')
	{
		prm->tex.ptr_s = mlx_xpm_file_to_image(prm->mlx.ptr, file,
											&prm->tex.width, &prm->tex.height);
		if (prm->tex.ptr_s == NULL || prm->tex.width != 64 ||
														prm->tex.height != 64)
			ret_error(prm, ERR_INVALID_TEXTURE);
		prm->tex.s = (unsigned int *)mlx_get_data_addr(prm->tex.ptr_s,
							&prm->tex.bpp, &prm->tex.size, &prm->tex.endian);
	}
	else
		load_xpm_2(prm, file, type);
}
