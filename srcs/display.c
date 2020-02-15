/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:42:09 by mroux             #+#    #+#             */
/*   Updated: 2020/02/11 18:09:24 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		compute_fps(void)
{
	static clock_t	start = 0;
	static clock_t	end = 0;
	double			cpu_time_used;
	int				fps;

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	fps = 1.0 / cpu_time_used;
	start = clock();
	return (fps);
}

/*
** int		test_display(GameEngine *ge, s_img *img)
** {
** 	for(int x = 0; x<SCREEN_WIDTH;x++)
** 	{
** 		for (int y = 0; y< SCREEN_HEIGHT; y++)
** 		{
** 			for (int k =0; k<4;k++)
** 				img->data[y * img->size_line + x*4 + k] =
**	ge->textures[2].data[(y % 64) * ge->textures[2].size_line + (x%64)*4 + k];
** 		}
** 	}
** 	return 0;
** }
*/

int		img_vertline_put(int img_x, int draw_start, int draw_end,
						s_img *tex, int tex_x, s_img *img)
{
	int		img_y;
	int		b;
	double	tex_pos;
	int		n_tex;
	int		n_img;

	b = img->bits_per_pixels / 8;
	tex_pos = (draw_start - SCREEN_HEIGHT / 2 +
			(double)(draw_end - draw_start) / 2) *
			(double)TEX_HEIGHT / (double)(draw_end - draw_start);
	img_y = draw_start;
	while (img_y < draw_end)
	{
		n_tex = ((int)tex_pos & (TEX_HEIGHT - 1)) * tex->size_line + tex_x * b;
		n_img = img_y * img->size_line + img_x * b;
		img->data[n_img] = tex->data[n_tex];
		img->data[n_img + 1] = tex->data[n_tex + 1];
		img->data[n_img + 2] = tex->data[n_tex + 2];
		img->data[n_img + 3] = tex->data[n_tex + 3];
		tex_pos += (double)TEX_HEIGHT / (double)(draw_end - draw_start);
		img_y++;
	}
	return (0);
}

void	compute_img(GameEngine *ge, s_img *img)
{
	s_dda	dda;
	int		tex_x;
	int		n;
	char		*world_map;

	n = 0;
	world_map = ge->smap.p_map;
	img->p_img = mlx_new_image(ge->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->data = mlx_get_data_addr(img->p_img, &img->bits_per_pixels,
								&img->size_line, &img->endian);
	while (n < SCREEN_WIDTH)
	{
		tex_x = compute_dda(&dda, n, ge);
		img_vertline_put(n, dda.drawStart, dda.drawEnd,
			&ge->textures[world_map[dda.mapY * MAP_WIDTH + dda.mapX] - 1],
			tex_x, img);
		n++;
	}
}

int		draw(void *param)
{
	GameEngine	*ge;
	s_img		img;

	ge = (GameEngine *)param;
	compute_img(ge, &img);
	mlx_put_image_to_window(ge->mlx_ptr, ge->mlx_win, img.p_img, 0, 0);
	mlx_string_put(ge->mlx_ptr, ge->mlx_win, 0, 20,
		0x00FFFFFF, ft_strjoin("FPS", ft_itoa(compute_fps())));
	return (0);
}

/*
** 	test_display(ge, &img);
** 	mlx_put_image_to_window(ge->mlx_ptr, ge->mlx_win, img.p_img, 0, 0);
** 		mlx_string_put(ge->mlx_ptr, ge->mlx_win, 0, 20,
**		0x00FFFFFF, ft_strjoin("FPS", ft_itoa(compute_FPS())));
** 	return 0;
*/
