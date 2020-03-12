/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:25:19 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 10:39:40 by mroux            ###   ########.fr       */
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

int		start_flood(char **lines, int i, int j)
{
	(void)i;
	(void)j;
	(void)lines;

	
	return (OK);
}

int		flood_map(char **lines)
{
	int		i;
	int		j;
	i = 0;
	j = 0;

	while (lines[i] != 0)
	{
		while (lines[i][j] != 0)
		{
			if (lines[i][j] == ' ')
				if (start_flood(lines, i, j) == ERROR)
					return (ERROR);
			j++;
		}
		i++;
	}
	return (OK);
}