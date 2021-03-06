/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:02:45 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 17:13:34 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		load_map_dimensions(t_ge *ge, char *line)
{
	char	**param;
	int		i;
	int		maxw;
	int		maxh;

	mlx_get_screen_size(ge->mlx_ptr, &maxw, &maxh);
	param = ft_split(line, ' ');
	if (param == NULL || check_dim_param(param) != OK)
		return (ERROR_DIM);
	ge->screen_w = ft_atoi(param[1]);
	ge->screen_w = ge->screen_w > maxw ? maxw : ge->screen_w;
	ge->screen_h = ft_atoi(param[2]);
	ge->screen_h = ge->screen_h > maxh ? maxh : ge->screen_h;
	i = 0;
	while (param[i] != 0)
		free(param[i++]);
	free(param);
	ge->map.flags = ge->map.flags | FLAG_R;
	return (OK);
}

int		load_colors(t_ge *ge, char *line)
{
	char	**param;
	int		n;
	int		i;

	replace_comma(line);
	param = ft_split(line, ' ');
	if (param == NULL || check_color_param(param) != OK)
		return (ERROR_COLORS);
	n = ft_strcmp(param[0], "F") == 0 ? 0 : 1;
	ge->map.color[n].r = ft_atoi(param[1]);
	ge->map.color[n].v = ft_atoi(param[2]);
	ge->map.color[n].b = ft_atoi(param[3]);
	i = 0;
	while (param[i] != 0)
		free(param[i++]);
	free(param);
	if (n == 0)
		ge->map.flags = ge->map.flags | FLAG_F;
	else
		ge->map.flags = ge->map.flags | FLAG_C;
	return (OK);
}

int		load_sprite(t_ge *ge, char *line)
{
	t_sprite	*sprite_ref;
	char		**param;
	int			i;

	i = 0;
	param = ft_split(line, ' ');
	if (param == NULL || check_sprite_param(param) != OK)
		return (ERROR_SPRITE);
	sprite_ref = &ge->map.sprite_ref;
	sprite_ref->texture.path = param[1];
	init_sprite_ref(sprite_ref, ge);
	i++;
	i = 0;
	while (param[i] != 0)
		free(param[i++]);
	free(param);
	ge->map.flags = ge->map.flags | FLAG_S;
	return (OK);
}

int		load_textures(t_ge *ge, char *line)
{
	t_img	*tex;
	char	**param;
	int		i;

	param = ft_split(line, ' ');
	if (param == NULL || check_tex_param(param) != OK)
		return (ERROR_TEX);
	tex = &ge->map.textures[get_tex_orientation(line[0])];
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
	flag_textures(ge, line);
	return (OK);
}
