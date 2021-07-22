/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 21:30:31 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 13:08:50 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	pixel(t_all *prm, int index, unsigned int color)
{
	int	r;
	int	g;
	int	b;

	if (color >= NONE)
		return (prm->img.adr[index]);
	else if (color < 256 * 256 * 256)
		return (color);
	r = (color / (256 * 256) % 256);
	g = (color / 256 % 256);
	b = (color % 256);
	r += (prm->img.adr[index] / (256 * 256) % 256);
	g += (prm->img.adr[index] / 256 % 256);
	b += (prm->img.adr[index] % 256);
	return (r * 256 * 256 + g * 256 + b);
}

static void			draw(t_all *prm, int locate, double dist)
{
	const double	size = prm->win.y / dist / 1.5;
	unsigned int	color;
	int				index;
	int				i;
	int				j;

	i = 0;
	j = 0;
	locate -= size;
	while (i < size)
	{
		while ((locate + i >= 0 && locate + i < prm->win.x) &&
				(j < size && prm->stk[locate + i].d > dist))
		{
			color = 64 * floor(64 * (double)j / size) + (double)i / size * 64;
			color = prm->tex.spr[color];
			index = locate + i + (prm->win.y / 2 + j) * prm->win.x;
			if (index < prm->win.x * prm->win.y)
				prm->img.adr[index] = pixel(prm, index, color);
			j++;
		}
		i++;
		j = 0;
	}
}

static void			locate(t_all *prm, double dir_x,
										double dir_y, double dist)
{
	double	angle;

	dir_x = (dir_x - prm->pos.x) / dist;
	dir_y = (dir_y - prm->pos.y) / dist;
	if (dir_y <= 0)
		angle = acos(dir_x) * RADIAN;
	else
		angle = 360 - acos(dir_x) * RADIAN;
	angle = prm->dir.a - angle + 30;
	if (angle >= 180)
		angle -= 360;
	else if (angle <= -180)
		angle += 360;
	draw(prm, angle * prm->win.x / 60, dist);
}

static void			position(t_all *prm)
{
	t_spr	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < prm->map.spr - 1)
	{
		j = i + 1;
		while (j < prm->map.spr)
		{
			if (prm->spr[i].d < prm->spr[j].d)
			{
				tmp = prm->spr[i];
				prm->spr[i] = prm->spr[j];
				prm->spr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void				draw_items(t_all *prm)
{
	const double	dist = hypot(prm->dir.x, prm->dir.y);
	int				i;

	if (prm->dir.y <= 0)
		prm->dir.a = acos(prm->dir.x / dist) * RADIAN;
	else
		prm->dir.a = 360 - acos(prm->dir.x / dist) * RADIAN;
	i = 0;
	while (i < prm->map.spr)
	{
		prm->spr[i].d = hypot(prm->spr[i].x - prm->pos.x,
								prm->spr[i].y - prm->pos.y);
		i++;
	}
	position(prm);
	i = 0;
	while (i < prm->map.spr)
	{
		locate(prm, prm->spr[i].x, prm->spr[i].y, prm->spr[i].d);
		i++;
	}
}
