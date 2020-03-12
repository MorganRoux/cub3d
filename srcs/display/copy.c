/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:19:57 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 12:04:49 by mroux            ###   ########.fr       */
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

void	copy_ceil(t_ge *ge, int *img_n, t_img *img, t_dda *dda)
{
	while (dda->img_y < dda->draw_start_y)
	{
		img->data[*img_n] = ge->map.color[0].r;
		img->data[*img_n + 1] = ge->map.color[0].v;
		img->data[*img_n + 2] = ge->map.color[0].b;
		img->data[*img_n + 3] = 0x00;
		dda->img_y++;
		*img_n += img->size_line;
	}
}

void	copy_floor(t_ge *ge, int *img_n, t_img *img, t_dda *dda)
{
	while (dda->img_y < ge->screen_h)
	{
		img->data[*img_n] = ge->map.color[1].r;
		img->data[*img_n + 1] = ge->map.color[1].v;
		img->data[*img_n + 2] = ge->map.color[1].b;
		img->data[*img_n + 3] = 0x00;
		dda->img_y++;
		*img_n += img->size_line;
	}
}
