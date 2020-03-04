/*
**	a byte is 4 bits but we are creating a 24 bit image so we can represent a pixel with 3
**	our final file size of our image is the width * height * 4 + size of bitmap header
**	pixels per meter https://www.wikiwand.com/en/Dots_per_inch
**	bitmap file header (14 bytes)
**	we could be savages and just create 2 array but since this is for learning lets
**	use structs so it can be parsed by someone without having to refer to the spec
**
**	since we have a non-natural set of bytes, we must explicitly tell the
**	compiler to not pad anything, on gcc the attribute alone doesn't work so
**	a nifty trick is if we declare the smallest data type last the compiler
**	*might* ignore padding, in some cases we can use a pragma or gcc's
**	__attribute__((__packed__)) when declaring the struct
**	we do this so we can have an accurate sizeof() which should be 14, however
**	this won't work here since we need to order the bytes as they are written
*/

#include "cub3d.h"



void	init_struct()
{

}
int		img_to_bmp(t_img *img, char *file_name)
{
	// create a file object that we will use to write our image
	int						fl;
	char					*pxl;
	int						iy;
	int						ix;
	t_bfh	bfh;
	t_bih 	bih;
	// we want to know how many pixels to reserve
	int image_size = img->w * img->h;
	int file_size = 54 + 3 * image_size;

	//int ppm = 300 * 39.375;

	memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size       = file_size;
	bfh.reserved1       = 0;
	bfh.reserved2       = 0;
	bfh.offset_bits     = 0;

	bih.size_header     = sizeof(bih);
	bih.width           = img->w;
	bih.height          = img->h;
	bih.planes          = 1;
	bih.bit_count       = 24;
	bih.compression     = 0;
	bih.image_size      = 3 * image_size;
	bih.ppm_x           = 0;//ppm;
	bih.ppm_y           = 0;//ppm;
	bih.clr_used        = 0;
	bih.clr_important   = 0;

	if ((fl = open(file_name, O_CREAT | O_RDWR)) == -1)
		printf("error %d\n", errno);
	write(fl, &bfh, 14);
	write(fl, &bih, sizeof(bih));
	iy = img->h - 1; 
	while (iy >= 0) 
	{
		ix = 0;
		while(ix < img->w)
		{
			pxl = &img->data[4 * (iy * img->w + ix)];
			if (write(fl, pxl, 3) == -1)
				printf("error %d\n", errno);
			ix++;
		}
		iy--;
	}
	close(fl);
	return (OK);
}