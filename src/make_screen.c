/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 23:06:31 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 15:12:16 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	make_raycasting_dir(t_all *prm)
{
	double	angle;
	double	dist;

	angle = ((double)prm->ray.i - (prm->win.x / 2)) * ANGLE / (prm->win.x / 2);
	prm->ray.x = prm->dir.x * cos(angle) - prm->dir.y * sin(angle);
	prm->ray.y = prm->dir.y * cos(angle) + prm->dir.x * sin(angle);
	dist = hypot(prm->ray.x, prm->ray.y);
	prm->ray.x /= dist;
	prm->ray.y /= dist;
	if (prm->ray.x >= 0)
		prm->ray.v = 1;
	else
		prm->ray.v = 0;
	if (prm->ray.y >= 0)
		prm->ray.w = 1;
	else
		prm->ray.w = 0;
}

static void	make_vertical(t_all *prm)
{
	double	x;
	double	y;

	x = floor(prm->pos.x) + prm->ray.v;
	y = prm->pos.y + (x - prm->pos.x) * (prm->ray.y / prm->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < prm->map.y)
	{
		if (prm->map.tab[(int)floor(y)][(int)(x - 1 + prm->ray.v)] == '1')
		{
			prm->hit.x = x;
			prm->hit.y = y;
			prm->hit.d = hypot(x - prm->pos.x, y - prm->pos.y);
			return ;
		}
		x += (prm->ray.v == 1 ? 1 : -1);
		y += (prm->ray.v == 1 ? 1 : -1) * prm->ray.y / prm->ray.x;
	}
	prm->hit.d = 10000;
	prm->hit.x = prm->pos.x;
	prm->hit.y = prm->pos.y;
}

static void	make_horizontal(t_all *prm)
{
	double	y;
	double	x;

	y = floor(prm->pos.y) + prm->ray.w;
	x = prm->pos.x + (y - prm->pos.y) * (prm->ray.x / prm->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < prm->map.x)
	{
		if (prm->map.tab[(int)(y - 1 + prm->ray.w)][(int)floor(x)] == '1')
		{
			if (prm->hit.d > hypot(x - prm->pos.x, y - prm->pos.y))
			{
				prm->hit.x = x;
				prm->hit.y = y;
				prm->hit.d = hypot(x - prm->pos.x, y - prm->pos.y);
			}
			return ;
		}
		y += (prm->ray.w == 1 ? 1 : -1);
		x += (prm->ray.w == 1 ? 1 : -1) * prm->ray.x / prm->ray.y;
	}
}

static void	init_screen(t_all *prm)
{
	prm->ray.x = 0;
	prm->ray.y = 0;
	prm->ray.i = 0;
	prm->ray.v = 0;
	prm->ray.w = 0;
	prm->hit.x = 0;
	prm->hit.y = 0;
	prm->hit.d = 0;
	prm->img.bpp = 0;
	prm->img.size = 0;
	prm->img.endian = 0;
}

void		make_screen(t_all *prm)
{
	init_screen(prm);
	prm->img.ptr = mlx_new_image(prm->mlx.ptr, prm->win.x, prm->win.y);
	prm->img.adr = (unsigned int *)mlx_get_data_addr(prm->img.ptr,
					&prm->img.bpp, &prm->img.size, &prm->img.endian);
	if (!(prm->stk = malloc(sizeof(t_stk) * prm->win.x)))
		ret_error(prm, ERR_MALLOC);
	prm->ray.i = 0;
	while (prm->ray.i < prm->win.x)
	{
		make_raycasting_dir(prm);
		make_vertical(prm);
		make_horizontal(prm);
		prm->stk[prm->ray.i].x = prm->ray.x;
		prm->stk[prm->ray.i].y = prm->ray.y;
		prm->stk[prm->ray.i].d = prm->hit.d;
		fence(prm, cor_view(prm));
		prm->ray.i++;
	}
	draw_items(prm);
	free(prm->stk);
}
