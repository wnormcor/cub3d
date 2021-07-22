/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 21:26:54 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/26 23:03:41 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			press_key(int key, t_all *prm)
{
	if (key == ESC)
	{
		prm->key.esc = 1;
		close_prog(prm, OK_STATUS);
	}
	else if (key == W)
		prm->key.w = 1;
	else if (key == S)
		prm->key.s = 1;
	else if (key == A)
		prm->key.a = 1;
	else if (key == D)
		prm->key.d = 1;
	else if (key == LEFT)
		prm->key.left = 1;
	else if (key == RIGHT)
		prm->key.right = 1;
	return (0);
}

int			release_key(int key, t_all *prm)
{
	if (key == W)
		prm->key.w = 0;
	else if (key == S)
		prm->key.s = 0;
	else if (key == A)
		prm->key.a = 0;
	else if (key == D)
		prm->key.d = 0;
	else if (key == LEFT)
		prm->key.left = 0;
	else if (key == RIGHT)
		prm->key.right = 0;
	return (0);
}
