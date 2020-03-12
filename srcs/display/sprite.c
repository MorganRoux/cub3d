/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:28:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 17:00:26 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		transform_sprite(t_ge *ge, t_sprite *sprite)
{
	t_dda	*dda;
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	dda = &ge->dda;
	sprite_x = sprite->pos.x - ge->pl.pos.x;
	sprite_y = sprite->pos.y - ge->pl.pos.y;
	inv_det = 1.0 / (ge->plane.x * ge->dir.y - ge->dir.x * ge->plane.y);
	dda->transform_x = inv_det * (ge->dir.y * sprite_x - ge->dir.x * sprite_y);
	dda->transform_y = inv_det *
				(-ge->plane.y * sprite_x + ge->plane.x * sprite_y);
	dda->stripe_screen_x = (int)((ge->screen_w / 2) *
				(1 + dda->transform_x / dda->transform_y));
}

void		compute_dim(t_ge *ge)
{
	t_dda	*dda;

	dda = &ge->dda;
	dda->sprite_height = abs((int)(ge->screen_h / (dda->transform_y)));
	dda->draw_start_y = -dda->sprite_height / 2 + ge->screen_h / 2;
	if (dda->draw_start_y < 0)
		dda->draw_start_y = 0;
	dda->draw_end_y = dda->sprite_height / 2 + ge->screen_h / 2;
	if (dda->draw_end_y >= ge->screen_h)
		dda->draw_end_y = ge->screen_h - 1;
	dda->sprite_width = abs((int)(ge->screen_h / (dda->transform_y)));
	dda->draw_start_x = -dda->sprite_width / 2 + dda->stripe_screen_x;
	if (dda->draw_start_x < 0)
		dda->draw_start_x = 0;
	dda->draw_end_x = dda->sprite_width / 2 + dda->stripe_screen_x;
	if (dda->draw_end_x >= ge->screen_w)
		dda->draw_end_x = ge->screen_w - 1;
}

void		draw_line(t_ge *ge, t_img *img, t_img *tex, t_pxl v)
{
	int		d;
	int		img_n;
	int		tex_n;

	d = (v.y) * 256 - ge->screen_h * 128 + ge->dda.sprite_height * 128;
	ge->dda.tex_y = ((d * TEX_HEIGHT) / ge->dda.sprite_height) / 256;
	img_n = v.y * img->size_line + v.x * (img->bits_per_pxl / 8);
	tex_n = ((int)ge->dda.tex_y & (TEX_HEIGHT - 1)) * tex->size_line
			+ ge->dda.tex_x * (img->bits_per_pxl / 8);
	if ((tex->data[tex_n] & 0x00FFFFFF) != 0)
		copy_pxl(&(img->data[img_n]), &(tex->data[tex_n]),
				img->bits_per_pxl / 8);
}

void		draw_sprite_to_img(t_ge *ge, t_img *tex, t_img *img)
{
	t_dda	*dda;
	t_pxl	v;

	dda = &ge->dda;
	v.x = dda->draw_start_x;
	while (v.x < dda->draw_end_x)
	{
		dda->tex_x = (int)(256 *
			(v.x - (-dda->sprite_width / 2 + dda->stripe_screen_x))
			* TEX_WIDTH / dda->sprite_width) / 256;
		if (dda->transform_y > 0 && v.x > 0 && v.x < ge->screen_w
			&& dda->transform_y < dda->z_buffer[v.x])
		{
			v.y = dda->draw_start_y;
			while (v.y < dda->draw_end_y)
			{
				draw_line(ge, img, tex, v);
				v.y++;
			}
		}
		v.x++;
	}
}

int			draw_sprite(t_ge *ge, t_img *img)
{
	t_img	*tex;
	int		i;

	i = 0;
	sort_sprite(ge, ge->dda.sprite_order, ge->dda.sprite_distance);
	while (i < ge->map.n_sprite)
	{
		tex = &ge->map.sprites[ge->dda.sprite_order[i]].texture;
		transform_sprite(ge, &ge->map.sprites[ge->dda.sprite_order[i]]);
		compute_dim(ge);
		draw_sprite_to_img(ge, tex, img);
		i++;
	}
	return (OK);
}
