/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:19:57 by mroux             #+#    #+#             */
/*   Updated: 2020/02/19 16:21:12 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_pxl(char *dest, char *source, int bpp)
{
	int i;

	i = -1;
	while (++i < bpp)
		dest[i] = source[i];
}

void	copy_ceil(int *img_y, t_game_engine *ge, int *img_n, t_img *img, t_dda *dda)
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

void	copy_floor(int *img_y, t_game_engine *ge, int *img_n, t_img *img)
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
