#include "cub3d.h"
extern void		*mlx_ptr;
extern void		*mlx_win;

extern s_img		textures[8];
extern const char *tex_dir;
extern char 		*tex_path[100];
extern int worldMap[MAP_HEIGHT][MAP_WIDTH];

int		compute_FPS()
{
	//Compute FPS
	static clock_t	start = 0;
	static clock_t	end = 0;
    double cpu_time_used;
    int FPS;

	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	FPS = 1.0 / cpu_time_used;
	start = clock();
	return (FPS);
}

int		test_display(s_img *img)
{
	for(int x = 0; x<SCREEN_WIDTH;x++)
	{
		for (int y = 0; y< SCREEN_HEIGHT; y++)
		{
			for (int k =0; k<4;k++)
				img->data[y * img->size_line + x*4 + k] = textures[2].data[(y % 64) * textures[2].size_line + (x%64)*4 + k]; 
		}
	}
	return 0;
}

int		img_vertline_put(int img_x, int drawStart, int drawEnd, s_img *tex, int tex_x, s_img *img)
{
	int img_y;
	int b;
	double temp;
	int tex_y;

	b = img->bits_per_pixels / 8;
	temp = 0; // texPos = (drawStart - SCREEN_HEIGHT / 2 + (double)(drawEnd - drawStart) / 2) * step;
	img_y = drawStart;
	while (img_y < drawEnd)
	{
		tex_y = (int)temp & (TEX_HEIGHT - 1);
		img->data[img_y * img->size_line + img_x * b] = tex->data[tex_y * tex->size_line + tex_x * b]; 
		img->data[img_y * img->size_line + img_x * b + 1] = tex->data[tex_y * tex->size_line + tex_x * b + 1];
		img->data[img_y * img->size_line + img_x * b + 2] = tex->data[tex_y * tex->size_line + tex_x * b + 2];
		img->data[img_y * img->size_line + img_x * b + 3] = tex->data[tex_y * tex->size_line + tex_x * b + 3];
		temp += (double)TEX_HEIGHT / (double)(drawEnd - drawStart);
		img_y++;
	}
	return 0;
}

int		draw(void *param)
{
	GameEngine	*ge;
	s_img		img;	
	s_dda		dda;
	int			n;
	int			tex_x;
	
	ge = (GameEngine *)param;
	n = 0;
	img.p_img = mlx_new_image (mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT );
	img.data = mlx_get_data_addr(img.p_img, &img.bits_per_pixels, &img.size_line, &img.endian);
	while(n < SCREEN_WIDTH)
	{
		tex_x = compute_dda(&dda, n, ge);
		img_vertline_put(n, dda.drawStart, dda.drawEnd, &textures[worldMap[dda.mapX][dda.mapY] - 1], tex_x, &img);
		n++;
	}
	mlx_put_image_to_window(mlx_ptr, mlx_win, img.p_img, 0, 0);
	mlx_string_put(mlx_ptr, mlx_win, 0, 20, 0x00FFFFFF, ft_strjoin("FPS", ft_itoa(compute_FPS())));
	return 0;
}

	// test_display(&img);
	// mlx_put_image_to_window(mlx_ptr, mlx_win, img.p_img, 0, 0);
	// 	mlx_string_put(mlx_ptr, mlx_win, 0, 20, 0x00FFFFFF, ft_strjoin("FPS", ft_itoa(compute_FPS())));
	// return 0;
