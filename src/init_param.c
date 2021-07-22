/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 21:29:28 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 16:22:12 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_win_img_map_tex(t_all *prm)
{
	prm->win.ptr = NULL;
	prm->win.x = 0;
	prm->win.y = 0;
	prm->img.ptr = NULL;
	prm->img.adr = NULL;
	prm->map.tab = NULL;
	prm->map.x = 0;
	prm->map.y = 0;
	prm->map.spr = 0;
	prm->map.count = 0;
	prm->map.pos = 0;
	prm->tex.ptr_n = NULL;
	prm->tex.ptr_s = NULL;
	prm->tex.ptr_e = NULL;
	prm->tex.ptr_w = NULL;
	prm->tex.ptr_spr = NULL;
	prm->tex.n = NULL;
	prm->tex.s = NULL;
	prm->tex.e = NULL;
	prm->tex.w = NULL;
	prm->tex.spr = NULL;
	prm->tex.c = NONE;
	prm->tex.f = NONE;
}

void	init_pos_dir_key(t_all *prm)
{
	prm->pos.x = 0;
	prm->pos.y = 0;
	prm->dir.x = 0;
	prm->dir.y = 0;
	prm->dir.a = 0;
	prm->spr = NULL;
	prm->stk = NULL;
	prm->key.w = 0;
	prm->key.s = 0;
	prm->key.a = 0;
	prm->key.d = 0;
	prm->key.esc = 0;
	prm->key.right = 0;
	prm->key.left = 0;
}

void	initialization(t_all *prm)
{
	prm->key.w = 1;
	move_forward(prm);
	prm->key.w = 0;
	prm->key.right = 1;
	move_rotate(prm);
	prm->key.right = 0;
	prm->key.s = 1;
	move_back(prm);
	prm->key.s = 0;
	prm->key.left = 1;
	move_rotate(prm);
	prm->key.left = 0;
}
