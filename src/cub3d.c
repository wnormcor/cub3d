/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:29:17 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 16:45:13 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			hook_loop(t_all *prm)
{
	if (prm->key.w == 1)
		move_forward(prm);
	if (prm->key.s == 1)
		move_back(prm);
	if (prm->key.a == 1)
		move_left(prm);
	if (prm->key.d == 1)
		move_right(prm);
	if (prm->key.left || prm->key.right)
		move_rotate(prm);
	make_screen(prm);
	mlx_put_image_to_window(prm->mlx.ptr, prm->win.ptr, prm->img.ptr, 0, 0);
	mlx_destroy_image(prm->mlx.ptr, prm->img.ptr);
	return (0);
}

int			main(int argc, char **argv)
{
	t_all	prm;

	if (!((argc == 2 && ext_cub(argv[1])) ||
		(argc == 3 && ext_cub(argv[1]) && argv_save(argv[2]))))
	{
		ft_putstr_fd("Error\nWrong arguments\n", 1);
		return (0);
	}
	init_win_img_map_tex(&prm);
	init_pos_dir_key(&prm);
	prm.mlx.ptr = mlx_init();
	parcer(&prm, argv[1]);
	if (argc == 3)
		save_bmp(&prm);
	prm.win.ptr = mlx_new_window(prm.mlx.ptr, prm.win.x, prm.win.y, "Cub3D");
	initialization(&prm);
	mlx_hook(prm.win.ptr, 17, 1L << 17, close_prog, &prm);
	mlx_hook(prm.win.ptr, 2, 1L << 0, press_key, &prm);
	mlx_hook(prm.win.ptr, 3, 1L << 1, release_key, &prm);
	mlx_loop_hook(prm.mlx.ptr, hook_loop, &prm);
	mlx_loop(prm.mlx.ptr);
	return (0);
}
