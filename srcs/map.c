/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:14:07 by mroux             #+#    #+#             */
/*   Updated: 2020/02/11 18:47:26 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	check_line(GameEngine *ge, int fd, char *line)
{
	if (line[0] == 'R')
		load_map_dimensions(ge, line);
	else if (line[0] == 'F' || line[0] == 'C')
		load_colors(ge, line);
	else if (line[0] == 'S')
		load_sprite(ge, line);
	else if (line[0] == '1')
		load_map(ge, fd, line);
	else if (line[0] == 'NO' || line[0] == 'SO' || 
		line[0] == 'EA' || line[0] == 'WE')
		load_textures(ge, line);
}

int		load_cub_file(GameEngine *ge, char *path)
{
	int		fd;
	char	*line;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	while(get_next_line(fd, &line))
		check_line(ge, fd, line);
	check_line(ge, fd, line);
	return (1);
}