/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 21:29:35 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 16:48:01 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_all *prm)
{
	prm->pos.x += (prm->dir.x * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '1')
		prm->pos.x -= (prm->dir.x * SPEED);
	prm->pos.y += (prm->dir.y * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '1')
		prm->pos.y -= (prm->dir.y * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '2')
	{
		prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] = '0';
		prm->map.spr--;
		check_item(prm);
	}
}

void	move_back(t_all *prm)
{
	prm->pos.x -= (prm->dir.x * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '1')
		prm->pos.x += (prm->dir.x * SPEED);
	prm->pos.y -= (prm->dir.y * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '1')
		prm->pos.y += (prm->dir.y * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '2')
	{
		prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] = '0';
		prm->map.spr--;
		check_item(prm);
	}
}

void	move_left(t_all *prm)
{
	prm->pos.x += (prm->dir.y * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '1')
		prm->pos.x -= (prm->dir.y * SPEED);
	prm->pos.y -= (prm->dir.x * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '1')
		prm->pos.y += (prm->dir.x * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '2')
	{
		prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] = '0';
		prm->map.spr--;
		check_item(prm);
	}
}

void	move_right(t_all *prm)
{
	prm->pos.x -= (prm->dir.y * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '1')
		prm->pos.x += (prm->dir.y * SPEED);
	prm->pos.y += (prm->dir.x * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '1')
		prm->pos.y -= (prm->dir.x * SPEED);
	if (prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] == '2')
	{
		prm->map.tab[(int)floor(prm->pos.y)][(int)floor(prm->pos.x)] = '0';
		prm->map.spr--;
		check_item(prm);
	}
}

void	move_rotate(t_all *prm)
{
	double	dist;

	if (prm->key.left == 1)
	{
		prm->dir.x = prm->dir.x * cos(-STEP) - prm->dir.y * sin(-STEP);
		prm->dir.y = prm->dir.y * cos(-STEP) + prm->dir.x * sin(-STEP);
		dist = hypot(prm->dir.x, prm->dir.y);
		prm->dir.x /= dist;
		prm->dir.y /= dist;
	}
	if (prm->key.right == 1)
	{
		prm->dir.x = prm->dir.x * cos(STEP) - prm->dir.y * sin(STEP);
		prm->dir.y = prm->dir.y * cos(STEP) + prm->dir.x * sin(STEP);
		dist = hypot(prm->dir.x, prm->dir.y);
		prm->dir.x /= dist;
		prm->dir.y /= dist;
	}
}
