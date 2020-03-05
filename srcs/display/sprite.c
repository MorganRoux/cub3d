/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:28:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/05 18:47:35 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap(int *sprite_order, double *sprite_distance)
{
	double		temp;

	temp = sprite_distance[0];
	sprite_distance[0] = sprite_distance[1];
	sprite_distance[1] = temp;
	temp = sprite_order[0];
	sprite_order[0] = sprite_order[1];
	sprite_order[1] = (int)temp;
}

void	sort_loop(int *sprite_order, double *sprite_distance)
{
	char		continu;
	int			i;
	
	i = 0;
	continu = 1;
	while (continu)
	{
		continu = 0;
		while (i < SPRITE_NUMBER - 1)
		{
			if (sprite_distance[i] < sprite_distance[i + 1])
			{
				continu = 1;
				swap(&sprite_order[i],&sprite_distance[i]);
			}
			i++;
		}
	}
}

void	sort_sprite(t_game_engine *ge, int *sprite_order, double *sprite_distance)
{
	t_sprite	*sprite;
	
	sprite = ge->map.sprite;
	for(int i = 0; i < SPRITE_NUMBER; i++)
    {
      sprite_order[i] = i;
      sprite_distance[i] = ((ge->pl.pos.x - sprite[i].pos.x) * (ge->pl.pos.x - sprite[i].pos.x) 
	  			+ (ge->pl.pos.y - sprite[i].pos.y) * (ge->pl.pos.y - sprite[i].pos.y));
    }
	sort_loop(sprite_order, sprite_distance);
}

/*
**	transform sprite with the inverse camera matrix
**	[ planeX   dirX ] -1                                       [ dirY      -dirX ]
**	[               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
**	[ planeY   dirY ]                                          [ -planeY  planeX ]
*/

void		transform_sprite(t_game_engine *ge, t_sprite *sprite)
{
	t_dda *dda;
	double sprite_x;
	double sprite_y;
	double inv_det;

	dda = &ge->dda;
	sprite_x = sprite->pos.x - ge->pl.pos.x;
	sprite_y = sprite->pos.y - ge->pl.pos.y;
	inv_det = 1.0 / (ge->plane.x * ge->dir.y - ge->dir.x * ge->plane.y);
	dda->transform_x = inv_det * (ge->dir.y * sprite_x - ge->dir.x * sprite_y);
	dda->transform_y = inv_det * (-ge->plane.y * sprite_x + ge->plane.x * sprite_y);
	dda->stripe_screen_x = (int)((ge->screen_w / 2) * (1 + dda->transform_x / dda->transform_y));
}

void		compute_dim(t_game_engine *ge)
{
	t_dda	*dda;

	dda = &ge->dda;
	dda->sprite_height = abs((int)(ge->screen_h / (dda->transform_y)));
	dda->draw_start_y = -dda->sprite_height / 2 + ge->screen_h / 2;
	if(dda->draw_start_y < 0) 
		dda->draw_start_y = 0;
	dda->draw_end_y = dda->sprite_height / 2 + ge->screen_h / 2;
	if(dda->draw_end_y >= ge->screen_h) 
		dda->draw_end_y = ge->screen_h - 1;
	dda->sprite_width = abs( (int) (ge->screen_h / (dda->transform_y)));
	dda->draw_start_x = -dda->sprite_width / 2 + dda->stripe_screen_x;
	if(dda->draw_start_x < 0) 
		dda->draw_start_x = 0;
	dda->draw_end_x = dda->sprite_width / 2 + dda->stripe_screen_x;
	if(dda->draw_end_x >= ge->screen_w) 
		dda->draw_end_x = ge->screen_w - 1;
}

void		draw_sprite(t_game_engine *ge, t_img *img)
{

	int			sprite_order[SPRITE_NUMBER];
	double		sprite_distance[SPRITE_NUMBER];
	t_dda		*dda;
	t_img		*tex;

	dda = &ge->dda;
	sort_sprite(ge, sprite_order, sprite_distance);
    for(int i = 0; i < SPRITE_NUMBER; i++)
    {
		tex = &ge->map.sprite[sprite_order[i]].texture;
		transform_sprite(ge, &ge->map.sprite[sprite_order[i]]);
		compute_dim(ge);
		for(int x = dda->draw_start_x; x < dda->draw_end_x; x++)
		{
			int texX = (int)(256 * (x - (-dda->sprite_width / 2 + dda->stripe_screen_x)) * TEX_WIDTH / dda->sprite_width) / 256;		
			if(dda->transform_y > 0 && x > 0 && x < ge->screen_w && dda->transform_y < dda->z_buffer[x])
			{	
				for(int y = dda->draw_start_y; y < dda->draw_end_y; y++)
				{
					int d = (y) * 256 - ge->screen_h * 128 + dda->sprite_height * 128;
					int texY = ((d * TEX_HEIGHT) / dda->sprite_height) / 256;
					int img_n = y * img->size_line + x * (img->bits_per_pxl / 8);
					int tex_n = ((int)texY & (TEX_HEIGHT - 1)) * tex->size_line
							+ texX * (img->bits_per_pxl / 8);
					if ((tex->data[tex_n] & 0x00FFFFFF) != 0)
						copy_pxl(&(img->data[img_n]), &(tex->data[tex_n]),
						img->bits_per_pxl / 8);
				}
			}
    	}
    }
}