/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:24:49 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 17:38:27 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# include <unistd.h>
# include <math.h>
# include <fcntl.h>

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

# define SPEED 0.1
# define STEP 0.03

# define ANGLE 0.52359877559
# define RADIAN 57.2957795131
# define NONE 0xFF000000

# define OK_STATUS 1
# define ERR_FD 2
# define ERR_GNL 3
# define ERR_INVALID_RESOL 4
# define ERR_INVALID_FC 5
# define ERR_MALLOC 6
# define ERR_INVALID_TEXTURE 7
# define ERR_INVALID_LINE 8
# define ERR_INVALID_MAP 9
# define ERR_NO_RESOL 10
# define ERR_MISS_TEXTURE 11
# define ERR_MISS_COLOR_FC 12
# define ERR_START_POSITION 13
# define ERR_MAP_NOT_CLOSED 14

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
}				t_win;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
	int				bpp;
	int				size;
	int				endian;
}				t_img;

typedef struct	s_map
{
	char			**tab;
	int				x;
	int				y;
	int				spr;
	int				count;
	int				pos;
}				t_map;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*spr;
	unsigned int	c;
	unsigned int	f;
	void			*ptr_n;
	void			*ptr_s;
	void			*ptr_e;
	void			*ptr_w;
	void			*ptr_spr;
	int				width;
	int				height;
	int				bpp;
	int				size;
	int				endian;
}				t_tex;

typedef struct	s_pos
{
	double			x;
	double			y;
}				t_pos;

typedef struct	s_dir
{
	double			x;
	double			y;
	double			a;
}				t_dir;

typedef struct	s_ray
{
	double			x;
	double			y;
	int				i;
	double			v;
	double			w;
}				t_ray;

typedef struct	s_hit
{
	double			x;
	double			y;
	double			d;
}				t_hit;

typedef struct	s_spr
{
	double			x;
	double			y;
	double			d;
}				t_spr;

typedef struct	s_stk
{
	double			x;
	double			y;
	double			d;
}				t_stk;

typedef struct	s_key
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				esc;
	int				right;
	int				left;
}				t_key;

typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_map			map;
	t_tex			tex;
	t_pos			pos;
	t_dir			dir;
	t_ray			ray;
	t_hit			hit;
	t_spr			*spr;
	t_stk			*stk;
	t_key			key;
}				t_all;

void			init_win_img_map_tex(t_all *prm);
void			init_pos_dir_key(t_all *prm);
void			initialization(t_all *prm);

void			parcer(t_all *prm, char *cub);

int				check_param(t_all *prm);
int				check_exten(const char *av, const char *str);
int				ext_cub(const char *av);
int				argv_save(const char *av);

void			load_map(t_all *prm, char *line, int *i);
void			load_texture(t_all *prm, char *line, int *i, char type);
void			load_xpm(t_all *prm, char *file, char type);

void			check_item(t_all *prm);
void			set_player_pos(t_all *prm);
void			set_fc_colors(t_all *prm, char *line, int *i, char type);
void			set_resolution(t_all *prm, char *line, int *i);

void			make_screen(t_all *prm);

int				cor_view(t_all *prm);
void			fence(t_all *prm, int fish);

void			draw_items(t_all *prm);

int				get_digits(char *line, int *i);
int				pass_space(char *line, int *i);
int				ret_error(t_all *prm, int err_num);

int				press_key(int key, t_all *prm);
int				release_key(int key, t_all *prm);
int				close_prog(t_all *prm, int err_num);

void			move_forward(t_all *prm);
void			move_back(t_all *prm);
void			move_left(t_all *prm);
void			move_right(t_all *prm);
void			move_rotate(t_all *prm);

void			save_bmp(t_all *prm);

#endif
