/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:42:09 by mroux             #+#    #+#             */
/*   Updated: 2020/02/18 11:00:25 by mroux            ###   ########.fr       */
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
** 	for(int x = 0; x<ge->screen_w;x++)
** 	{
** 		for (int y = 0; y< ge->screen_h; y++)
** 		{
** 			for (int k =0; k<4;k++)
** 				img->data[y * img->size_line + x*4 + k] =
**	ge->smap.textures[2].data[(y % 64) * ge->smap.textures[2].size_line + (x%64)*4 + k];
** 		}
** 	}
** 	return 0;
** }
*/

void	copy_pxl(char *dest, char *source, int bpp)
{
	int i;
	i = -1;
	while (++i < bpp)
		dest[i] = source[i];
}

void	copy_ceil(int *img_y, GameEngine *ge, int *img_n, t_img *img, t_dda *dda)
{
	while (*img_y < dda->draw_start)
	{
		img->data[*img_n] = ge->smap.color[0].r;
		img->data[*img_n + 1] = ge->smap.color[0].v;
		img->data[*img_n + 2] = ge->smap.color[0].b;
		img->data[*img_n + 3] = 0x00;
		(*img_y)++;
		*img_n += img->size_line;
	}
}

void copy_floor(int *img_y, GameEngine *ge, int *img_n, t_img *img)
{
	while (*img_y < ge->screen_h)
	{
		img->data[*img_n] = ge->smap.color[1].r;
		img->data[*img_n + 1] = ge->smap.color[1].v;
		img->data[*img_n + 2] = ge->smap.color[1].b;
		img->data[*img_n + 3] = 0x00;
		(*img_y)++;
		*img_n += img->size_line;
	}
}

int		img_vertline_put(int img_x, t_dda *dda, GameEngine *ge,
						t_img *tex, int tex_x, t_img *img)
{
	double	tex_y;
	int		img_y;
	int		tex_n;
	int		img_n;

	tex_y = (dda->draw_start - ge->screen_h / 2 +
			(double)dda->line_height / 2) *
			(double)TEX_HEIGHT / dda->line_height;
	img_y = 0;
	img_n = img_y * img->size_line + img_x * (img->bits_per_pxl / 8);
	copy_ceil(&img_y, ge, &img_n, img, dda);
	while (img_y < dda->draw_end)
	{
		tex_n = ((int)tex_y & (TEX_HEIGHT - 1)) * tex->size_line + tex_x * (img->bits_per_pxl / 8);
		copy_pxl(&(img->data[img_n]), &(tex->data[tex_n]), img->bits_per_pxl / 8);
		tex_y += (double)TEX_HEIGHT / (double)(dda->line_height);
		img_y++;
		img_n += img->size_line;
	}
	copy_floor(&img_y, ge, &img_n, img);
	return (0);
}

void	compute_img(GameEngine *ge, t_img *img)
{
	t_dda	dda;
	int		tex_x;
	int		img_x;

	img_x = 0;
	img->p_img = mlx_new_image(ge->mlx_ptr, ge->screen_w, ge->screen_h);
	img->data = mlx_get_data_addr(img->p_img, &img->bits_per_pxl,
								&img->size_line, &img->endian);
	while (img_x < ge->screen_w)
	{
		tex_x = compute_dda(&dda, img_x, ge);
		img_vertline_put(img_x, &dda, ge,
			&ge->smap.textures[get_wall_orientation(&dda)],
			tex_x, img);
		img_x++;
	}
}

/* use to display different blocks -> cf lodev
**	img_vertline_put(img_x, &dda, ge,
**			&ge->smap.textures[ge->smap.p_map[dda.map_y * ge->smap.w + dda.map_x] - 1],
**			tex_x, img);
*/
int		draw(void *param)
{
	GameEngine	*ge;
	t_img		img;

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
