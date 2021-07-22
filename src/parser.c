/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:51:46 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 17:41:24 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			pass_space(char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
			|| (str[*i] == '\r' || str[*i] == '\v'))
		(*i)++;
	return (OK_STATUS);
}

static void	parcer_line(t_all *prm, char *s)
{
	int		i;

	i = 0;
	if ((s[i] == '1' || s[i] == ' ' || prm->map.count == 1)
		&& prm->map.count != 2)
		load_map(prm, s, &i);
	else if (s[i] == 'R' && s[i + 1] == ' ')
		set_resolution(prm, s, &i);
	else if (s[i] == 'S' && s[i + 1] == ' ')
		load_texture(prm, s, &i, 'I');
	else if (s[i] == 'F' && s[i + 1] == ' ')
		set_fc_colors(prm, s, &i, 'F');
	else if (s[i] == 'C' && s[i + 1] == ' ')
		set_fc_colors(prm, s, &i, 'C');
	else if (s[i] == 'N' && s[i + 1] == 'O' && s[i + 2] == ' ')
		load_texture(prm, s, &i, 'N');
	else if (s[i] == 'S' && s[i + 1] == 'O' && s[i + 2] == ' ')
		load_texture(prm, s, &i, 'S');
	else if (s[i] == 'W' && s[i + 1] == 'E' && s[i + 2] == ' ')
		load_texture(prm, s, &i, 'W');
	else if (s[i] == 'E' && s[i + 1] == 'A' && s[i + 2] == ' ')
		load_texture(prm, s, &i, 'E');
	if (pass_space(s, &i) && s[i] != '\0')
		ret_error(prm, ERR_INVALID_LINE);
}

void		get_max_width(t_all *prm, char *cub)
{
	char	*line;
	int		gnl_return;
	int		fd;

	line = NULL;
	gnl_return = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		ret_error(prm, ERR_FD);
	while (gnl_return == 1)
	{
		gnl_return = get_next_line(fd, &line);
		prm->map.x = (prm->map.x > (int)ft_strlen(line))
			? prm->map.x : (int)ft_strlen(line);
		free(line);
		line = NULL;
	}
	close(fd);
	if (gnl_return == -1)
		ret_error(prm, ERR_GNL);
}

void		parcer(t_all *prm, char *cub)
{
	char	*line;
	int		gnl_return;
	int		fd;

	get_max_width(prm, cub);
	line = NULL;
	gnl_return = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		ret_error(prm, ERR_FD);
	while (gnl_return == 1)
	{
		gnl_return = get_next_line(fd, &line);
		parcer_line(prm, line);
		free(line);
		line = NULL;
	}
	close(fd);
	if (gnl_return == -1)
		ret_error(prm, ERR_GNL);
	set_player_pos(prm);
	prm->spr = NULL;
	check_item(prm);
	check_param(prm);
}
