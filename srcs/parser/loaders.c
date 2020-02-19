/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:02:45 by mroux             #+#    #+#             */
/*   Updated: 2020/02/18 15:51:14 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int		load_map_dimensions(t_game_engine *ge, char *line)
{
	char	**param;
	int		i;

	param = ft_split(line, ' ');
	ge->screen_w = ft_atoi(param[1]);
	ge->screen_w =  ge->screen_w > 2560 ? 2560 : ge->screen_w;
	ge->screen_h = ft_atoi(param[2]);
	ge->screen_h =  ge->screen_h > 1440 ? 1440 : ge->screen_h;
	i = 0;
	while (param[i] != 0)
		free(param[i++]);
	free(param);
	
	return (OK);
}

int		load_colors(t_game_engine *ge, char *line)
{
	char	**param;
	int		n;
	int		i;

	param = ft_split(&(line[2]), ',');
	n = (line[0] == 'F') ? 0 : 1;
	ge->smap.color[n].r = ft_atoi(param[0]);
	ge->smap.color[n].v = ft_atoi(param[1]);
	ge->smap.color[n].b = ft_atoi(param[2]);
	i = 0;
	while (param[i] != 0)
		free(param[i++]);
	free(param);
	return (OK);
}

int		load_sprite(t_game_engine *ge, char *line)
{
	t_img	*sprite;
	char	**param;
	int		i;

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
				sprite->p_img, &sprite->bits_per_pxl,
				&sprite->size_line, &sprite->endian);
	i = 0;
	while (param[i] != 0)
		free(param[i++]);
	free(param);
	return (OK);
}

int		load_map(t_game_engine *ge, int fd, char *firstline)
{
	int		n;
	char	*line;

	n = 0;
	ge->smap.w = ft_strlen(firstline);
	ge->smap.h = 0;
	ge->smap.p_map = NULL;
	load_line(ge, firstline, &n);
	while(get_next_line(fd, &line))
	{
		load_line(ge, line, &n);
		free(line);
	}
	load_line(ge, line, &n);
	free(line);
	check_map(ge->smap.p_map);
	return (OK);
}

int			load_textures(t_game_engine *ge, char *line)
{
	t_img	*tex;
	char	**param;
	int		i;

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
				tex->p_img, &tex->bits_per_pxl,
				&tex->size_line, &tex->endian);
	i = 0;
	while (param[i] != 0)
		free(param[i++]);
	free(param);
	return (OK);
}