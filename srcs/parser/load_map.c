/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 09:28:49 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 18:16:16 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**load_lines(int fd, char *firstline)
{
	char	*line;
	char	**lines;
	int		n_lines;

	n_lines = 1;
	if (!(lines = (char **)malloc(sizeof(char *))) || *firstline == '\0')
		return (NULL);
	*lines = firstline;
	while (get_next_line(fd, &line))
	{
		if ((lines = create_new_line(lines, line, n_lines)) == NULL)
			return (NULL);
		n_lines++;
	}
	if ((lines = create_new_line(lines, line, n_lines)) == NULL)
		return (NULL);
	n_lines++;
	if ((lines = create_new_line(lines, NULL, n_lines)) == NULL)
		return (NULL);
	return (lines);
}

int		get_map_dimensions(char **lines, t_map *map)
{
	size_t	l;

	while (*lines != 0)
	{
		if (check_map_line(*lines) == ERROR)
			return (ERROR);
		if ((int)(l = ft_strlen(*lines)) > map->w)
			map->w = (int)l;
		lines++;
		map->h = map->h + 1;
	}
	if (map->w == 0 || map->h == 0)
		return (ERROR);
	map->size = map->w * map->h;
	return (OK);
}

int		create_map(char **lines, t_map *map)
{
	int		i;
	int		n;

	if (!(map->p_map = (char *)malloc(sizeof(char) * map->size)))
		return (ERROR);
	n = 0;
	while (*lines != 0)
	{
		i = 0;
		while ((*lines)[i] != 0)
		{
			if ((*lines)[i] == ' ')
				map->p_map[n] = 0;
			else
				map->p_map[n] = (*lines)[i] - '0';
			n++;
			i++;
		}
		lines++;
	}
	return (OK);
}

int		load_map(t_ge *ge, int fd, char *firstline)
{
	char	**lines;

	lines = 0;
	ge->map.w = 0;
	ge->map.h = 0;
	ge->map.p_map = NULL;
	if ((lines = load_lines(fd, ft_strdup(firstline))) == NULL)
		return (ERROR_MAP);
	if (get_map_dimensions(lines, &ge->map) == ERROR)
		return (ERROR_MAP);
	if (make_rect(ge->map.w, lines) == ERROR)
		return (ERROR_MAP);
	if (flood_map(&ge->map, lines) == ERROR)
		return (ERROR_MAP);
	if (create_map(lines, &ge->map) == ERROR)
		return (ERROR_MAP);
	if (check_map(ge) == ERROR)
		return (ERROR_MAP);
	free_lines(lines);
	free(lines);
	ge->map.flags = ge->map.flags | FLAG_MAP;
	return (OK);
}
