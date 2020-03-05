/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:28:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/05 17:52:49 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite(t_game_engine *ge, int *sprite_order, double *sprite_distance)
{
	t_sprite	*sprite;
	char		continu;
	int			i;
	double		temp;
	i = 0;
	continu = 1;
	sprite = ge->map.sprite;
	for(int i = 0; i < SPRITE_NUMBER; i++)
    {
      sprite_order[i] = i;
      sprite_distance[i] = ((ge->pl.pos.x - sprite[i].pos.x) * (ge->pl.pos.x - sprite[i].pos.x) 
	  			+ (ge->pl.pos.y - sprite[i].pos.y) * (ge->pl.pos.y - sprite[i].pos.y));
    }
	while (continu)
	{
		continu = 0;
		while (i < SPRITE_NUMBER - 1)
		{
			if (sprite_distance[i] < sprite_distance[i + 1])
			{
				continu = 1;
				temp = sprite_distance[i];
				sprite_distance[i] = sprite_distance[i + 1];
				sprite_distance[i + 1] = temp;
				temp = sprite_order[i];
				sprite_order[i] = sprite_order[i + 1];
				sprite_order[i + 1] = (int)temp;
			}
			i++;
		}
	}
    //sortSprites(spriteOrder, spriteDistance, SPRITE_NUMBER);
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
	//translate sprite position to relative to camera
	sprite_x = sprite->pos.x - ge->pl.pos.x;
	sprite_y = sprite->pos.y - ge->pl.pos.y;
	inv_det = 1.0 / (ge->plane.x * ge->dir.y - ge->dir.x * ge->plane.y); //required for correct matrix multiplication
	dda->transform_x = inv_det * (ge->dir.y * sprite_x - ge->dir.x * sprite_y);
	dda->transform_y = inv_det * (-ge->plane.y * sprite_x + ge->plane.x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D
	dda->stripe_screen_x = (int)((ge->screen_w / 2) * (1 + dda->transform_x / dda->transform_y));
}

void		draw_sprite(t_game_engine *ge, t_img *img)
{

	int			sprite_order[SPRITE_NUMBER];
	double		sprite_distance[SPRITE_NUMBER];
	t_dda		*dda;
	t_sprite	*sprite;
	t_img		*tex;

	dda = &ge->dda;
	sort_sprite(ge, sprite_order, sprite_distance);
    for(int i = 0; i < SPRITE_NUMBER; i++)
    {
		
		sprite = &ge->map.sprite[sprite_order[i]];
		tex = &sprite->texture;
		transform_sprite(ge, sprite);
		//calculate height of the sprite on screen
		dda->stripe_height = abs((int)(ge->screen_h / (dda->transform_y))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -dda->stripe_height / 2 + ge->screen_h / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = dda->stripe_height / 2 + ge->screen_h / 2;
		if(drawEndY >= ge->screen_h) drawEndY = ge->screen_h - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (ge->screen_h / (dda->transform_y)));
		int drawStartX = -spriteWidth / 2 + dda->stripe_screen_x;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + dda->stripe_screen_x;
		if(drawEndX >= ge->screen_w) drawEndX = ge->screen_w - 1;
		//loop through every vertical stripe of the sprite on screen
		for(int x = drawStartX; x < drawEndX; x++)
		{
			int texX = (int)(256 * (x - (-spriteWidth / 2 + dda->stripe_screen_x)) * TEX_WIDTH / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance			
			if(dda->transform_y > 0 && x > 0 && x < ge->screen_w && dda->transform_y < dda->z_buffer[x])
			{	
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - ge->screen_h * 128 + dda->stripe_height * 128; //256 and 128 factors to avoid floats
					int texY = ((d * TEX_HEIGHT) / dda->stripe_height) / 256;
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