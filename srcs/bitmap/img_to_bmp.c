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

struct bitmap_file_header {
		unsigned char   bitmap_type[2];     // 2 bytes
		int             file_size;          // 4 bytes
		short           reserved1;          // 2 bytes
		short           reserved2;          // 2 bytes
		unsigned int    offset_bits;        // 4 bytes
} bfh;

// bitmap image header (40 bytes)
struct bitmap_image_header {
	unsigned int    size_header;        // 4 bytes
	unsigned int    width;              // 4 bytes
	unsigned int    height;             // 4 bytes
	short int       planes;             // 2 bytes
	short int       bit_count;          // 2 bytes
	unsigned int    compression;        // 4 bytes
	unsigned int    image_size;         // 4 bytes
	unsigned int    ppm_x;              // 4 bytes
	unsigned int    ppm_y;              // 4 bytes
	unsigned int    clr_used;           // 4 bytes
	unsigned int    clr_important;      // 4 bytes
} bih;

int		img_to_bmp(t_img *img, char *file_name)
{
	// create a file object that we will use to write our image
	int fl;
	// we want to know how many pixels to reserve
	int image_size = img->w * img->h;
	int file_size = 54 + 4 * image_size;

	int ppm = 300 * 39.375;

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
	bih.image_size      = file_size;
	bih.ppm_x           = ppm;
	bih.ppm_y           = ppm;
	bih.clr_used        = 0;
	bih.clr_important   = 0;

	fl = open(file_name, O_CREAT | O_RDWR);

	write(fl, &bfh, 14);
	write(fl, &bih, 40);
	printf("ok");
	for (int i = 0; i < image_size; i++) 
	{
		unsigned char color[3] = {
			img->data[4 * i + 2], img->data[4 * i + 1], img->data[4 * i]
		};	
		write(fl, color, sizeof(color));

	}
	close(fl);
	return (OK);
}