/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:25:19 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 18:16:04 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_player(char c)
{
	if (c == 'N' || c == 'S' ||
		c == 'E' || c == 'W')
		return (1);
	return (0);
}

int		flood(char **lines, int i, int j, t_map *map)
{
	if (i < 0 || i >= map->h)
		return (OK);
	if (j < 0 || j >= map->w)
		return (OK);
	if (is_player(lines[i][j]) == 1)
		return (ERROR);
	if (lines[i][j] == '1' || lines[i][j] == '8' || lines[i][j] == '9')
		return (OK);
	lines[i][j] = (lines[i][j] == '0') ? '8' : '9';
	if (flood(lines, i - 1, j, map) == ERROR ||
		flood(lines, i + 1, j, map) == ERROR ||
		flood(lines, i, j - 1, map) == ERROR ||
		flood(lines, i, j + 1, map))
		return (ERROR);
	return (OK);
}

int		flood_conditions(char **lines, int i, int j, t_map *map)
{
	if ((lines[i][j] == '2' || lines[i][j] == '0') &&
		(i == 0 || i + 1 == map->h || j == 0 || j + 1 == map->w))
		return (OK);
	return (ERROR);
}

int		flood_map(t_map *map, char **lines)
{
	int		i;
	int		j;

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
