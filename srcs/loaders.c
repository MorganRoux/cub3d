/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:02:45 by mroux             #+#    #+#             */
/*   Updated: 2020/02/13 20:29:33 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		load_map_dimensions(GameEngine *ge, char *line)
{
	char	**param;

	param = ft_split(line, ' ');
	ge->smap.w = ft_atoi(param[1]);
	ge->smap.h = ft_atoi(param[2]);
	while (*param != 0)
		free(*param++);
	return (OK);
}

int		load_colors(GameEngine *ge, char *line)
{
	char	**param;
	int		n;

	param = ft_split(&(line[2]), ',');
	n = (line[0] == 'F') ? 0 : 1;
	ge->smap.color[n].r = ft_atoi(param[0]);
	ge->smap.color[n].v = ft_atoi(param[1]);
	ge->smap.color[n].b = ft_atoi(param[2]);
	while (*param != 0)
		free(*param++);
	return (OK);
}

int		load_sprite(GameEngine *ge, char *line)
{
	s_img	*sprite;
	char	**param;

	param = ft_split(line, ' ');
	sprite = &ge->smap.sprite;
	sprite->path = param[1];
	sprite->p_img = mlx_xpm_file_to_image(
					ge->mlx_ptr,
					sprite->path,
					&sprite->w, &sprite->h);
	if (sprite->p_img == 0)
		return (ERROR);
	sprite->data = mlx_get_data_addr(
				sprite->p_img, &sprite->bits_per_pixels,
				&sprite->size_line, &sprite->endian);
	while (*param != 0)
		free(*param++);
	return (OK);
}

int		load_line(GameEngine *ge, char *line, int *n)
{
	if ((int)ft_strlen(line) != ge->smap.w)
	{
		printf("arg");
		return (ERROR);
	}
	if (!(ge->smap.p_map = ft_strnjoin(ge->smap.p_map, line, ft_strlen(ge->smap.p_map) + ge->smap.w)))
		return ERROR;
	if (*line != '1')
		return (ERROR);
	while(*line != 0)
		ge->smap.p_map[(*n)++]= *line++ - '0';
	n--;
	if (*--line != '1')
		return (ERROR);
	return (OK);
}

int		check_map(void)
{
	return (0);
}

int		load_map(GameEngine *ge, int fd, char *firstline)
{
	int		n;
	char	*line;

	n = 0;
	ge->smap.w = ft_strlen(firstline);
	if (!(ge->smap.p_map = (char *)malloc(sizeof(char))))
		return (ERROR);
	ge->smap.p_map[0]= 0;
	load_line(ge, firstline, &n);
	while(get_next_line(fd, &line))
	{
		load_line(ge, line, &n);
		free(line);
	}
	load_line(ge, line, &n);
	free(line);
	check_map();
	return (OK);
}
int		get_tex_orientation(char l)
{
	if (l == 'N')
		return (0);
	if (l == 'S')
		return (1);
	if (l == 'E')
		return (2);
	if (l == 'W')
		return (3);
	return (ERROR);
}

int		load_textures(GameEngine *ge, char *line)
{
	s_img	*tex;
	char	**param;

	param = ft_split(line, ' ');
	tex = &ge->smap.textures[get_tex_orientation(line[0])];
	tex->path = param[1];
	tex->p_img = mlx_xpm_file_to_image(
					ge->mlx_ptr,
					tex->path,
					&tex->w, &tex->h);
	if (tex->p_img == 0)
		return (ERROR);
	tex->data = mlx_get_data_addr(
				tex->p_img, &tex->bits_per_pixels,
				&tex->size_line, &tex->endian);
	while (*param != 0)
		free(*param++);
	return (OK);
}