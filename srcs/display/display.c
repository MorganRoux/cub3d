/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:42:09 by mroux             #+#    #+#             */
/*   Updated: 2020/03/05 11:25:19 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		img_vertline_put(t_dda *dda, t_game_engine *ge,
						t_img *tex, t_img *img)
{
	int		tex_n;
	int		img_n;

	dda->tex_y = (dda->draw_start - ge->screen_h / 2 +
			(double)dda->line_height / 2) *
			(double)TEX_HEIGHT / dda->line_height;
	dda->img_y = 0;
	img_n = dda->img_y * img->size_line + dda->img_x * (img->bits_per_pxl / 8);
	copy_ceil(ge, &img_n, img, dda);
	while (dda->img_y < dda->draw_end)
	{
		tex_n = ((int)dda->tex_y & (TEX_HEIGHT - 1)) * tex->size_line
				+ dda->tex_x * (img->bits_per_pxl / 8);
		copy_pxl(&(img->data[img_n]), &(tex->data[tex_n]),
				img->bits_per_pxl / 8);
		dda->tex_y += (double)TEX_HEIGHT / (double)(dda->line_height);
		dda->img_y++;
		img_n += img->size_line;
	}
	copy_floor(ge, &img_n, img, dda);
	return (0);
}

void	compute_img(t_game_engine *ge, t_img *img)
{
	t_dda	*dda;

	dda = &ge->dda;
	init_dda(dda, ge);
	img->p_img = mlx_new_image(ge->mlx_ptr, ge->screen_w, ge->screen_h);
	img->w = ge->screen_w;
	img->h = ge->screen_h;
	img->data = mlx_get_data_addr(img->p_img, &img->bits_per_pxl,
								&img->size_line, &img->endian);
	while (dda->img_x < ge->screen_w)
	{
		compute_dda(dda, ge);
		img_vertline_put(dda, ge,
			&ge->map.textures[get_wall_orientation(dda)], img);
		dda->img_x++;
	}
}

/*
**	use to display different blocks -> cf lodev
**	img_vertline_put(img_x, &dda, ge,
**	&ge->smap.textures[ge->smap.p_map[dda.map_y * ge->smap.w + dda.map_x] - 1],
**	tex_x, img);
*/

int		draw(void *param)
{
	t_game_engine	*ge;
	t_img			img;

	ge = (t_game_engine *)param;
	compute_img(ge, &img);
	mlx_put_image_to_window(ge->mlx_ptr, ge->mlx_win, img.p_img, 0, 0);
	mlx_destroy_image(ge->mlx_ptr, img.p_img);
	return (0);
}

/*
**	Compute FPS
**
**	mlx_string_put(ge->mlx_ptr, ge->mlx_win, 0, 20,
**	0x00FFFFFF, ft_strjoin("FPS", ft_itoa(compute_fps())));
*/
