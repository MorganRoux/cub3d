/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:25:19 by mroux             #+#    #+#             */
/*   Updated: 2020/03/10 18:23:21 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int		make_rect(int w, char **lines)
{
	int		i;
	int		l;

	i = 0;
	while (lines[i] != 0)
	{
		l = ft_strlen(lines[i]);
		if ((lines[i] = (char *)ft_realloc(lines[i], l, w + 1)) == NULL)
			return (ERROR);
		while (l < w)
			lines[i][l++] = ' ';
		i++;
	}
	return (OK);
}

int		flood(char **lines, int i, int j, t_map *map)
{
	if (i < 0 || i >= map->h)
		return (OK);
	if (j < 0 || j >= map->w)
		return (OK);
	if (ft_isalpha(lines[i][j]) == 1)
		return (ERROR);
	if (lines[i][j] == '1' || lines[i][j] == '8')
		return (OK);
	lines[i][j] = '8';
	if (flood(lines, i - 1, j, map) == ERROR ||
		flood(lines, i + 1, j, map) == ERROR ||
		flood(lines, i, j - 1, map) == ERROR ||
		flood(lines, i, j + 1, map))
		return (ERROR);
	return (OK);
}

int		flood_conditions(char **lines, int i, int j, t_map *map)
{
	(void)map;
	if ((lines[i][j] == ' ' || lines[i][j] == '2' || lines[i][j] == '0') &&
		(i == 0 || i + 1 == map->h || j == 0 || j + 1 == map->w))
		return (OK);
	return (ERROR);
}

int		flood_map(t_map *map, char **lines)
{
	char 	**s;
	int		i;
	int		j;
	s = lines;
	i = 0;
	while (lines[i] != 0)
	{
		j = 0;
		while (lines[i][j] != 0)
		{
			if (flood_conditions(lines, i, j, map) == OK)
			{
				if (flood(lines, i, j, map) == ERROR)
					return (ERROR);
			}
			j++;
		}
		i++;
	}
	return (OK);
}