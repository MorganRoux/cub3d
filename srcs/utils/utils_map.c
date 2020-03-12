/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:02:45 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 17:58:56 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_map_line(char *line)
{
	(void)line;
	while (*line != 0)
	{
		if (*line != '0' && *line != '1' &&
			*line != '2' && *line != 'N' &&
			*line != 'S' && *line != 'E' &&
			*line != 'W' && *line != ' ')
			return (ERROR);
		line++;
	}
	return (OK);
}

void	free_lines(char **lines)
{
	while (*lines != 0)
		free(*lines++);
}

char	**create_new_line(char **lines, char *newline, int n_lines)
{
	if ((lines = ft_realloc(lines, n_lines * sizeof(char *),
					(n_lines + 1) * sizeof(char *))) == NULL)
		return (NULL);
	lines[n_lines] = newline;
	return (lines);
}

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

void	print_map(char **lines)
{
	while (*lines != 0)
		printf("%s\n", *lines++);
	getchar();
}
