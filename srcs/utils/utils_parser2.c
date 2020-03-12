/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:32:06 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 17:19:37 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		replace_comma(char *line)
{
	while (*line != 0)
	{
		if (*line == ',')
			*line = ' ';
		line++;
	}
}

void		print_map(char **lines)
{
	printf("\n");
	while (*lines != 0)
		printf("%s\n", *lines++);
	getchar();
}

int			init_sprite_ref(t_sprite *sprite_ref, t_ge *ge)
{
	sprite_ref->texture.p_img = mlx_xpm_file_to_image(
					ge->mlx_ptr,
					sprite_ref->texture.path,
					&sprite_ref->texture.w, &sprite_ref->texture.h);
	if (sprite_ref->texture.p_img == 0)
		return (ERROR);
	sprite_ref->texture.data = mlx_get_data_addr(
				sprite_ref->texture.p_img, &sprite_ref->texture.bits_per_pxl,
				&sprite_ref->texture.size_line, &sprite_ref->texture.endian);
	return (OK);
}

void		flag_textures(t_ge *ge, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		ge->map.flags = ge->map.flags | FLAG_NO;
	if (ft_strncmp(line, "SO", 2) == 0)
		ge->map.flags = ge->map.flags | FLAG_SO;
	if (ft_strncmp(line, "EA", 2) == 0)
		ge->map.flags = ge->map.flags | FLAG_EA;
	if (ft_strncmp(line, "WE", 2) == 0)
		ge->map.flags = ge->map.flags | FLAG_WE;
}
