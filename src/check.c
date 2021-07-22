/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:29:04 by wnormcor          #+#    #+#             */
/*   Updated: 2020/10/27 16:15:26 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_exten(const char *av, const char *str)
{
	const int	len = ft_strlen(str);

	if (ft_strncmp(&av[ft_strlen(av) - len], str, len) == 0)
		return (OK_STATUS);
	return (0);
}

int		ext_cub(const char *av)
{
	return (check_exten(av, ".cub"));
}

int		argv_save(const char *av)
{
	if (ft_strncmp(av, "--save", 6) == 0)
		return (OK_STATUS);
	return (0);
}

void	check_map(t_all *prm)
{
	int	y;
	int	x;

	y = 0;
	while (y < prm->map.y)
	{
		x = 0;
		while (x < prm->map.x)
		{
			if ((prm->map.tab[y][x] == '0' || prm->map.tab[y][x] == '2'
			|| prm->map.tab[y][x] == 'N' || prm->map.tab[y][x] == 'S'
			|| prm->map.tab[y][x] == 'E' || prm->map.tab[y][x] == 'W') &&
			(y == 0 || y == prm->map.y - 1 || x == 0 || x == prm->map.x - 1))
				ret_error(prm, ERR_MAP_NOT_CLOSED);
			else if ((prm->map.tab[y][x] == '0' || prm->map.tab[y][x] == '2'
			|| prm->map.tab[y][x] == 'N' || prm->map.tab[y][x] == 'S'
			|| prm->map.tab[y][x] == 'E' || prm->map.tab[y][x] == 'W') &&
			(prm->map.tab[y - 1][x] == ' ' || prm->map.tab[y + 1][x] == ' ' ||
			prm->map.tab[y][x + 1] == ' ' || prm->map.tab[y][x - 1] == ' '))
				ret_error(prm, ERR_MAP_NOT_CLOSED);
			x++;
		}
		y++;
	}
}

int		check_param(t_all *prm)
{
	int	y;
	int	x;

	if (prm->win.x <= 0 || prm->win.y <= 0)
		ret_error(prm, ERR_NO_RESOL);
	else if ((prm->tex.n == NULL || prm->tex.s == NULL || prm->tex.e == NULL)
								|| (prm->tex.w == NULL || prm->tex.spr == NULL))
		ret_error(prm, ERR_MISS_TEXTURE);
	else if (prm->tex.c == NONE || prm->tex.f == NONE)
		ret_error(prm, ERR_MISS_COLOR_FC);
	else if (prm->map.pos != 1)
		ret_error(prm, ERR_START_POSITION);
	check_map(prm);
	y = 0;
	while (y < prm->map.y)
	{
		x = -1;
		while (++x < prm->map.x)
		{
			if (prm->map.tab[y][x] == ' ')
				prm->map.tab[y][x] = '1';
		}
		y++;
	}
	return (OK_STATUS);
}
