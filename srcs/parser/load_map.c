/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 09:28:49 by mroux             #+#    #+#             */
/*   Updated: 2020/03/10 12:06:08 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int		load_map(t_game_engine *ge, int fd, char *firstline)
// {
// 	int		n;
// 	char	*line;

// 	n = 0;
// 	ge->map.w = ft_strlen(firstline);
// 	ge->map.h = 0;
// 	ge->map.p_map = NULL;


// 	load_line(ge, firstline, &n);
// 	while (get_next_line(fd, &line))
// 	{
// 		load_line(ge, line, &n);
// 		free(line);
// 	}
// 	load_line(ge, line, &n);
// 	ge->map.size = n;
// 	free(line);
// 	check_map(ge);
// 	for(size_t j=0;j<ge->map.size;j++)
// 			printf("%c",(ge->map.p_map)[j] + '0');
// 	printf("\n");
// 	printf("%zu %d %d", ge->map.size, ge->map.h, ge->map.w);
// 	getchar();
// 	return (OK);
// }

int		erreur(char *err)
{
	printf("%s", err);
	getchar();
	return (ERROR);
}

int		check_map_line(char *line, int *flags)
{
	(void)line;
	(void)flags;
	return (OK);
}

char	**create_new_line(char **lines, char *newline, int n_lines)
{
	// if (ft_isdigit(*newline) == 0)
	// 	return (NULL);
	if ((lines = ft_realloc(lines, n_lines * sizeof(char *), 
					(n_lines + 1) * sizeof(char *))) == NULL)
		return (NULL);
	lines[n_lines] = newline;
	return (lines);
}

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
	free(line);
	return (lines);
}

int		get_map_dimensions(char **lines, t_map *map)
{
	int		flags;
	size_t	l;

	while (*lines != 0)
	{
		if (check_map_line(*lines, &flags) == ERROR)
			return (ERROR);
		if ((int)(l = ft_strlen(*lines)) > map->w)
			map->w = (int)l;
		lines++;
		map->h = map->h +1;
	}
	
	if (map->w == 0 || map->h == 0)
		return (ERROR);
	map->size = map->w * map->h;
	return (OK);
}

char	**flowd_map(int w, int h, char **lines)
{
	(void)w;
	(void)h;
	(void)lines;
	return (NULL);
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
			map->p_map[n++] = (*lines)[i++] - '0';
		lines++;
	}
	return (OK);
}

int		load_map(t_game_engine *ge, int fd, char *firstline)
{
	int		n;
	char	**lines;

	n = 0;
	lines = 0;
	ge->map.w = 0;
	ge->map.h = 0;
	ge->map.p_map = NULL;
	if ((lines = load_lines(fd, firstline)) == NULL)
		return (ERROR_MAP);
	get_map_dimensions(lines, &ge->map);
	// if ((lines = flowd_map(ge->map.w, ge->map.h, lines)) == NULL)
	// 	return (ERROR_MAP);
	if(create_map(lines, &ge->map) == ERROR)
		return (ERROR_MAP);
	check_map(ge);
	for(size_t j=0;j<ge->map.size;j++)
			printf("%c",(ge->map.p_map)[j] + '0');
	printf("\n");
	printf("%zu %d %d", ge->map.size, ge->map.h, ge->map.w);
	getchar();
	return (OK);
}