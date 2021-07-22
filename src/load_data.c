/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 21:30:00 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 17:37:05 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_xpm(t_all *prm, char *file, char type)
{
	int		fd;

	prm->tex.width = 0;
	prm->tex.height = 0;
	prm->tex.bpp = 0;
	prm->tex.size = 0;
	prm->tex.endian = 0;
	if (check_exten(file, ".xpm") != OK_STATUS)
		ret_error(prm, ERR_INVALID_TEXTURE);
	if ((fd = open(file, O_RDONLY)) == -1)
		ret_error(prm, ERR_INVALID_TEXTURE);
	close(fd);
	load_xpm(prm, file, type);
}

void			load_texture(t_all *prm, char *line, int *i, char type)
{
	char	*file;
	int		j;

	(*i) += 2;
	pass_space(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		ret_error(prm, ERR_MALLOC);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	set_xpm(prm, file, type);
	free(file);
}

static char		*get_map_line(t_all *prm, char *s, int *i)
{
	char	*res;
	int		j;

	if (!(res = malloc(sizeof(char) * (prm->map.x + 1))))
		ret_error(prm, ERR_MALLOC);
	j = 0;
	while (s[*i] != '\0')
	{
		if (s[*i] == '0' || s[*i] == '1' || s[*i] == 'N' || s[*i] == 'E' ||
		s[*i] == 'S' || s[*i] == 'W' || s[*i] == ' ' || s[*i] == '2')
			res[j++] = s[*i];
		else
		{
			free(res);
			return (NULL);
		}
		if (s[*i] == '2')
			prm->map.spr++;
		(*i)++;
	}
	while (j < prm->map.x)
		res[j++] = ' ';
	res[j] = '\0';
	return (res);
}

void			load_map(t_all *prm, char *line, int *i)
{
	char	**tmp_tab;
	int		j;

	if (line[*i] == '\0')
		prm->map.count = 2;
	else
		prm->map.count = 1;
	if (!(tmp_tab = malloc(sizeof(char *) * (prm->map.y + 2))))
		ret_error(prm, ERR_MALLOC);
	j = -1;
	while (++j < prm->map.y)
		tmp_tab[j] = prm->map.tab[j];
	if ((tmp_tab[prm->map.y] = get_map_line(prm, line, i)) == NULL)
	{
		free(tmp_tab);
		ret_error(prm, ERR_INVALID_MAP);
	}
	tmp_tab[prm->map.y + 1] = NULL;
	if (prm->map.y > 0)
		free(prm->map.tab);
	prm->map.tab = tmp_tab;
	prm->map.y++;
}
