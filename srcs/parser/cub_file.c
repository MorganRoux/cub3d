/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:14:07 by mroux             #+#    #+#             */
/*   Updated: 2020/03/09 18:58:04 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int		check_line(t_game_engine *ge, int fd, char *line)
{
	int r;

	if (line[0] == 'R')
		r = load_map_dimensions(ge, line);
	else if (line[0] == 'F' || line[0] == 'C')
		r = load_colors(ge, line);
	else if (ft_strncmp(line, "S ", 2) == 0)
		r = load_sprite(ge, line);
	else if (ft_isdigit(line[0]))
		r = load_map(ge, fd, line);
	else if (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0)
		r = load_textures(ge, line);
	else if (line[0] == '\0')
		r = OK;
	else
		r = ERROR;
	return (r);
}

int		load_cub_file(t_game_engine *ge, char *path)
{
	int		fd;
	char	*line;
	int		r;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (ERROR);
	while (get_next_line(fd, &line))
	{
		if ((r = check_line(ge, fd, line)) != OK)
			return (r);
		free(line);
	}
	if ((r = check_line(ge, fd, line)) != OK)
		return (r);
	free(line);
	return (OK);
}
