/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:14:07 by mroux             #+#    #+#             */
/*   Updated: 2020/02/18 11:16:16 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	check_line(t_game_engine *ge, int fd, char *line)
{
	if (line[0] == 'R')
	{
		printf("before dim");
		getchar();
		load_map_dimensions(ge, line);
		printf("after dim");
		getchar();
	}
	else if (line[0] == 'F' || line[0] == 'C')
	{
		printf("before colors");
		getchar();
		load_colors(ge, line);
	}
	else if (ft_strncmp(line, "S ", 2) == 0)
	{
		printf("before sprite");
		getchar();
		load_sprite(ge, line);
	}
	else if (ft_isdigit(line[0]))
	{
		printf("before map");
		getchar();
		load_map(ge, fd, line);
	}
	else if (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0)
		{ 
			printf("before tex");
			getchar();
		load_textures(ge, line);
		}
}

int		load_cub_file(t_game_engine *ge, char *path)
{
	int		fd;
	char	*line;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	while(get_next_line(fd, &line))
	{
		printf("before checkline");
		getchar();
		check_line(ge, fd, line);
		free(line);

	}
	check_line(ge, fd, line);
	free(line);
	return (1);
}