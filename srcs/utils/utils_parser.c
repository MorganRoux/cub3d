/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:40:47 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 17:12:47 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cardinal	get_tex_orientation(char l)
{
	if (l == 'N')
		return (NO);
	if (l == 'S')
		return (SO);
	if (l == 'E')
		return (EA);
	if (l == 'W')
		return (WE);
	return (-1);
}

int			load_line(t_ge *ge, char *line, int *n)
{
	if ((int)ft_strlen(line) != ge->map.w)
		return (ERROR);
	ge->map.h++;
	if (!(ge->map.p_map = ft_realloc(ge->map.p_map, *n, *n + ge->map.w)))
		return (ERROR);
	while (*line != 0)
		ge->map.p_map[(*n)++] = *line++ - '0';
	return (OK);
}

void		*ft_realloc(void *p, size_t l, size_t newsize)
{
	char	*ret;
	char	*ptr;
	size_t	n;

	n = -1;
	ptr = p;
	if (!(ret = (char *)malloc(newsize)))
		return (NULL);
	while (++n < l)
		ret[n] = ptr[n];
	while (n < newsize)
		ret[n++] = 0;
	if (p != NULL)
		free(p);
	return ((void *)ret);
}

int			check_number(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		if (!ft_isdigit(s[i++]))
			return (ERROR);
	return (OK);
}

void	replace_comma(char *line)
{
	while (*line != 0)
	{
		if (*line == ',')
			*line = ' ';
		line++;
	}
}

void	print_map(char **lines)
{
	printf("\n");
	while(*lines != 0)
		printf("%s\n", *lines++);
	getchar();
}

int		init_sprite_ref(t_sprite *sprite_ref, t_ge *ge)
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

void	flag_textures(t_ge *ge, char *line)
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
