/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 21:30:15 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/26 23:33:40 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	pixel(t_all *prm, double i)
{
	int	index;

	if (floor(prm->hit.y) == prm->hit.y)
	{
		index = 64 * floor(64 * i) + 64 * (prm->hit.x - floor(prm->hit.x));
		if (prm->ray.w == 1)
			return (prm->tex.s[index]);
		else if (prm->ray.w == 0)
			return (prm->tex.n[index]);
	}
	else if (floor(prm->hit.x) == prm->hit.x)
	{
		index = 64 * floor(64 * i) + 64 * (prm->hit.y - floor(prm->hit.y));
		if (prm->ray.v == 1)
			return (prm->tex.e[index]);
		else if (prm->ray.v == 0)
			return (prm->tex.w[index]);
	}
	return (NONE);
}

void				fence(t_all *prm, int fish)
{
	const int		start = prm->win.x * (prm->win.y - fish) / 2;
	unsigned int	color;
	int				count;

	if (fish > prm->win.y)
		count = (fish - prm->win.y) / 2;
	else
		count = 0;
	color = prm->tex.c;
	while (prm->ray.i < prm->win.x * prm->win.y)
	{
		if (prm->ray.i >= start && count < fish)
		{
			color = pixel(prm, (double)count / fish);
			count++;
		}
		else if (count == fish)
			color = prm->tex.f;
		prm->img.adr[prm->ray.i] = mlx_get_color_value(prm->mlx.ptr, color);
		prm->ray.i += prm->win.x;
	}
	prm->ray.i -= prm->win.x * prm->win.y;
}

int					cor_view(t_all *prm)
{
	double	correct;
	double	fisheye;

	fisheye = fabs((double)prm->ray.i / (prm->win.x / 2) - 1) * ANGLE;
	correct = (double)prm->hit.d * cos(fisheye);
	return (round(prm->win.y / correct));
}
