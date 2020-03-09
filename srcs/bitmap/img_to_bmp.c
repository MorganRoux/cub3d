/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:08:54 by mroux             #+#    #+#             */
/*   Updated: 2020/03/09 18:14:21 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_img *img, t_bfh *bfh, t_bih *bih)
{
	memcpy(&bfh->bitmap_type, "BM", 2);
	bfh->file_size = 54 + 4 * img->w * img->h;
	bfh->reserved1 = 0;
	bfh->reserved2 = 0;
	bfh->offset_bits = 54;
	bih->size_header = 40;
	bih->width = img->w;
	bih->height = img->h;
	bih->planes = 1;
	bih->bit_count = 32;
	bih->compression = 0;
	bih->image_size = 0;
	bih->ppm_x = 0;
	bih->ppm_y = 0;
	bih->clr_used = 0;
	bih->clr_important = 0;
}

int		write_header(t_img *img, int fl)
{
	t_bfh	bfh;
	t_bih	bih;

	init_struct(img, &bfh, &bih);
	write(fl, &bfh.bitmap_type, 2);
	write(fl, &bfh.file_size, 4);
	write(fl, &bfh.reserved1, 2);
	write(fl, &bfh.reserved2, 2);
	write(fl, &bfh.offset_bits, 4);
	write(fl, &bih.size_header, 4);
	write(fl, &bih.width, 4);
	write(fl, &bih.height, 4);
	write(fl, &bih.planes, 2);
	write(fl, &bih.bit_count, 2);
	write(fl, &bih.compression, 4);
	write(fl, &bih.image_size, 4);
	write(fl, &bih.ppm_x, 4);
	write(fl, &bih.ppm_y, 4);
	write(fl, &bih.clr_used, 4);
	write(fl, &bih.clr_important, 4);
	return (OK);
}

int		write_data(t_img *img, int fl)
{
	char	*pxl;
	int		iy;
	int		ix;

	iy = img->h - 1;
	while (iy >= 0)
	{
		ix = 0;
		while (ix < img->w)
		{
			pxl = &img->data[4 * (iy * img->w + ix)];
			if (write(fl, pxl, 4) == -1)
			{
				printf("error %d\n", errno);
				return (-1);
			}
			ix++;
		}
		iy--;
	}
	return (OK);
}

int		img_to_bmp(t_img *img, char *file_name)
{
	int		fl;

	if ((fl = open(file_name, O_CREAT | O_RDWR, 777)) == -1)
	{
		printf("error %d\n", errno);
		return (ERROR);
	}
	write_header(img, fl);
	write_data(img, fl);
	close(fl);
	return (OK);
}
