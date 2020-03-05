/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:28:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/05 17:06:14 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite(t_game_engine *ge, int *sprite_order, double *sprite_distance)
{
	t_sprite *sprite;

	sprite = ge->map.sprite;
	for(int i = 0; i < SPRITE_NUMBER; i++)
    {
      sprite_order[i] = i;
      sprite_distance[i] = ((ge->pl.pos.x - sprite[i].pos.x) * (ge->pl.pos.x - sprite[i].pos.x) 
	  			+ (ge->pl.pos.y - sprite[i].pos.y) * (ge->pl.pos.y - sprite[i].pos.y));
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
		// printf("%d %d %d %d %d\n", drawStartX, drawStartY, drawEndX, drawEndY, dda->stripe_height);
		// 			getchar();
		//loop through every vertical stripe of the sprite on screen
		for(int x = drawStartX; x < drawEndX; x++)
		{
			int texX = (int)(256 * (x - (-spriteWidth / 2 + dda->stripe_screen_x)) * TEX_WIDTH / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			// printf("%f %f %f %d\n", dda->transform_x, dda->transform_y, dda->z_buffer[x], x);
			// 		getchar();
			if(dda->transform_y > 0 && x > 0 && x < ge->screen_w && dda->transform_y < dda->z_buffer[x])
			{	
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					
					int d = (y) * 256 - ge->screen_h * 128 + dda->stripe_height * 128; //256 and 128 factors to avoid floats
					int texY = ((d * TEX_HEIGHT) / dda->stripe_height) / 256;
					// printf("%d %d", texY, texX);
					// getchar();
					//char color = 0x00;//sprite->texture.data[TEX_WIDTH * texY + texX]; //get current color from the texture
					//if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
					
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



// void sortSprites(int* order, double* dist, int amount)
// {
//   std::vector<std::pair<double, int>> sprites(amount);
//   for(int i = 0; i < amount; i++) {
//     sprites[i].first = dist[i];
//     sprites[i].second = order[i];
//   }
//   std::sort(sprites.begin(), sprites.end());
//   // restore in reverse order to go from farthest to nearest
//   for(int i = 0; i < amount; i++) {
//     dist[i] = sprites[amount - i - 1].first;
//     order[i] = sprites[amount - i - 1].second;
//   }
// }


// void		draw_sprite(t_game_engine *ge, t_img *img)
// {
// 	//arrays used to sort the sprites
// int spriteOrder[SPRITE_NUMBER];
// double spriteDistance[SPRITE_NUMBER];
// int h = ge->screen_h;
// int w = ge->screen_w;
// t_dda *dda = &ge->dda;
// t_sprite *sprite = ge->map.sprite;

// //SPRITE CASTING
//     //sort sprites from far to close
//     for(int i = 0; i < SPRITE_NUMBER; i++)
//     {
//       spriteOrder[i] = i;
//       spriteDistance[i] = ((ge->pl.pos.x - sprite[i].pos.x) * (ge->pl.pos.x - sprite[i].pos.x) + (ge->pl.pos.y - sprite[i].pos.y) * (ge->pl.pos.y - sprite[i].pos.y)); //sqrt not taken, unneeded
//     }
//     //sortSprites(spriteOrder, spriteDistance, SPRITE_NUMBER);

//     //after sorting the sprites, do the projection and draw them
//     for(int i = 0; i < SPRITE_NUMBER; i++)
//     {
//       //translate sprite position to relative to camera
//       double spriteX = sprite[spriteOrder[i]].pos.x - ge->pl.pos.x;
//       double spriteY = sprite[spriteOrder[i]].pos.y - ge->pl.pos.y;

//       //transform sprite with the inverse camera matrix
//       // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
//       // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
//       // [ planeY   dirY ]                                          [ -planeY  planeX ]

//       double invDet = 1.0 / (ge->plane.x * ge->dir.y - ge->dir.x * ge->plane.y); //required for correct matrix multiplication

//       double transformX = invDet * (ge->dir.y * spriteX - ge->dir.x * spriteY);
//       double transformY = invDet * (-ge->plane.y * spriteX + ge->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

//       int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

//       //calculate height of the sprite on screen
//       int spriteHeight = abs((int)(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
//       //calculate lowest and highest pixel to fill in current stripe
//       int drawStartY = -spriteHeight / 2 + h / 2;
//       if(drawStartY < 0) drawStartY = 0;
//       int drawEndY = spriteHeight / 2 + h / 2;
//       if(drawEndY >= h) drawEndY = h - 1;

//       //calculate width of the sprite
//       int spriteWidth = abs( (int) (h / (transformY)));
//       int drawStartX = -spriteWidth / 2 + spriteScreenX;
//       if(drawStartX < 0) drawStartX = 0;
//       int drawEndX = spriteWidth / 2 + spriteScreenX;
//       if(drawEndX >= w) drawEndX = w - 1;

//       //loop through every vertical stripe of the sprite on screen
//       for(int stripe = drawStartX; stripe < drawEndX; stripe++)
//       {
//         int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256;
//         //the conditions in the if are:
//         //1) it's in front of camera plane so you don't see things behind you
//         //2) it's on the screen (left)
//         //3) it's on the screen (right)
//         //4) ZBuffer, with perpendicular distance
//         if(transformY > 0 && stripe > 0 && stripe < w && transformY < dda->z_buffer[stripe])
//         for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
//         {
//           int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
//           int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
// 		  char color = 0x00;
// 			if((color & 0x00FFFFFF) != 0)
// 			{
// 				int img_n = y * img->size_line + stripe * (img->bits_per_pxl / 8);
// 				int tex_n = ((int)texY & (TEX_HEIGHT - 1)) * sprite[i].texture.size_line
// 						+ texX * (img->bits_per_pxl / 8);
// 				copy_pxl(&(img->data[img_n]), &(sprite[i].texture.data[tex_n]),
// 				img->bits_per_pxl / 8);
// 			}
//         }
//       }
//     }
// }