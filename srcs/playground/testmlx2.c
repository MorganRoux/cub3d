#include "cub3d.h"
#include <stdio.h>

int		mlx_vertline_put(int n, int drawStart, int drawEnd, int color, void *mlx_ptr, void *mlx_win)
{
	int i;

	i = drawStart;
	while (i < drawEnd)
	{
		mlx_pixel_put(mlx_ptr, mlx_win, n, i, color);
		i++;
	}
	return 0;
}

// int		img_vertline_put(int n, int drawStart, int drawEnd, int color, char *img_data)
// {
// 	int i;
// 	int b = bits_per_pixel / 8;
// 	unsigned int	ucolor;

// 	ucolor = mlx_get_color_value(mlx_ptr, color);
// 	i = drawStart;
// 	(void)ucolor;
// 	while (i < drawEnd)
// 	{
// 		//Blue
// 		img_data[i * size_line + n * b] = ucolor & 0xFF;
// 		// Green
// 		img_data[i * size_line + n * b + 1] = (ucolor >> 8) & 0xFF;
// 		// Red
// 		img_data[i * size_line + n * b + 2] = (ucolor >> 16) & 0xFF;
// 		// 
// 		img_data[i * size_line + n * b + 3] = (ucolor >> 24) & 0xFF;
// 		i++;
// 	}
// 	return 0;
// }

int		img_vertline_put(int img_line, int drawStart, int drawEnd, int *tex, int texX, char *img_data)
{
	int i;
	int b = bits_per_pixel / 8;
	unsigned int	ucolor;
	double step = (double)TEX_HEIGHT / (double)(drawEnd - drawStart);
	double texPos = 0;
	int texY;

	// texPos = (drawStart - SCREEN_HEIGHT / 2 + (double)(drawEnd - drawStart) / 2) * step;

	i = drawStart;
	while (i < drawEnd)
	{
		texY = (int)texPos & (TEX_HEIGHT - 1);
		ucolor = mlx_get_color_value(mlx_ptr, tex[texY * TEX_WIDTH + texX]);
		texPos += step;
		//Blue
		img_data[i * size_line + img_line * b] = ucolor & 0xFF;
		// Green
		img_data[i * size_line + img_line * b + 1] = (ucolor >> 8) & 0xFF;
		// Red
		img_data[i * size_line + img_line * b + 2] = (ucolor >> 16) & 0xFF;
		// 
		img_data[i * size_line + img_line * b + 3] = (ucolor >> 24) & 0xFF;
		i++;
	}
	return 0;
}

int		darken_color(int color, double dark)
{
	int red, green, blue;

	red = (color & 0x00FF0000) >> 16;
	green = (color & 0x0000FF00) >> 8;
	blue = (color & 0x000000FF);
	return ((int)(red * dark) << 16) + ((int)(green * dark) << 8) + ((int)(blue * dark));

}
int		extract_tex_vertline(int *tex, int *lb, int n)
{
	int i;

	i = 0;
	while (i<TEX_HEIGHT)
		*lb++ = tex[i++ * TEX_WIDTH + n];
	return 0;
}

int		draw(void *param)
{
	GameEngine	*ge;
	void		*img;
	char		*img_data;

	ge = (GameEngine *)param;

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
	int		drawStart;
	int		drawEnd;
	int		lineHeight;
	//int		color;
	//length of ray from current position to next x or y-side
	double	sideDistX;
	double	sideDistY;
	//length of ray from one x or y-side to next x or y-side
	double	deltaDistX;
	double	deltaDistY;
	double	rayDirX;
	double	rayDirY;
	double	cameraX;
	//what direction to step in x or y-direction (either +1 or -1)
	int		stepX;
	int		stepY;
	//which box of the map we're in
	int		mapX;
	int		mapY;
	int		side; //was a NS or a EW wall hit?
	int		hit = 0; //was there a wall hit?
	double	perpWallDist;

	//mlx_clear_window ( mlx_ptr, mlx_win );
	img = mlx_new_image (mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT );
	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	//printf("bpp : %ui - sl = %ui - endian = %ui", bits_per_pixel, size_line, endian);
	//getchar();

	for(int n = 0; n < SCREEN_WIDTH; n++)
	{
		//calculate ray position and direction
		cameraX = 2 * n / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
		rayDirX = ge->dir.x + ge->plane.x * cameraX;
		rayDirY = ge->dir.y + ge->plane.y * cameraX;
		//which box of the map we're in
		mapX = (int)(ge->pl.pos.x);
		mapY = (int)(ge->pl.pos.y);
		deltaDistX = fabs(1 / rayDirX); //sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = fabs(1 / rayDirY); //sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (ge->pl.pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - ge->pl.pos.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (ge->pl.pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - ge->pl.pos.y) * deltaDistY;
		}
		//perform DDA
		hit = 0;
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - ge->pl.pos.x + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - ge->pl.pos.y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawStart < 0)drawStart = 0;
		drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawEnd >= SCREEN_HEIGHT)drawEnd = SCREEN_HEIGHT - 1;

		// //choose wall color
		// switch(worldMap[mapX][mapY])
		// {
		// 	case 1:  color = 0x00FF0000;    break; //red
		// 	case 2:  color = 0x0000FF00;  break; //green
		// 	case 3:  color = 0x000000FF;   break; //blue
		// 	case 4:  color = 0x00FFFFFF;  break; //white
		// 	default: color = 0X00FFFF00; break; //yellow
		// }
		// //give x and y sides different brightness
		// if(side == 1) 
		// 	color = darken_color(color, 0.5);
		//calculate value of wallX
		
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = ge->pl.pos.y + perpWallDist * rayDirY;
		else           wallX = ge->pl.pos.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TEX_WIDTH));
		if(side == 0 && rayDirX > 0) texX = TEX_WIDTH - texX - 1;
		if(side == 1 && rayDirY < 0) texX = TEX_WIDTH - texX - 1;

		//draw the pixels of the stripe as a vertical line
		img_vertline_put(n, drawStart, drawEnd, texture[worldMap[mapX][mapY] - 1], texX, img_data);
	}
	
	mlx_put_image_to_window(mlx_ptr, mlx_win, img, 0, 0);
	return 0;
}

int		key_hook(int keycode,void *param)
{
	GameEngine *ge;

	ge = (GameEngine *)param;
	if(keycode == KEY_UP)
	{
		if(worldMap[(int)(ge->pl.pos.x + ge->dir.x * ge->moveSpeed)][(int)(ge->pl.pos.y)] == 0) 
			ge->pl.pos.x += ge->dir.x * ge->moveSpeed;
		if(worldMap[(int)(ge->pl.pos.x)][(int)(ge->pl.pos.y + ge->dir.y * ge->moveSpeed)] == 0) 
			ge->pl.pos.y += ge->dir.y * ge->moveSpeed;
	}
	if(keycode == KEY_DOWN)
	{
		if(worldMap[(int)(ge->pl.pos.x - ge->dir.x * ge->moveSpeed)][(int)(ge->pl.pos.y)] == 0) 
			ge->pl.pos.x -= ge->dir.x * ge->moveSpeed;
		if(worldMap[(int)(ge->pl.pos.x)][(int)(ge->pl.pos.y - ge->dir.y * ge->moveSpeed)] == 0) 
			ge->pl.pos.y -= ge->dir.y * ge->moveSpeed;
	}
	if(keycode == KEY_LEFT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = ge->dir.x;
		ge->dir.x = ge->dir.x * cos(ge->rotSpeed) - ge->dir.y * sin(ge->rotSpeed);
		ge->dir.y = oldDirX * sin(ge->rotSpeed) + ge->dir.y * cos(ge->rotSpeed);
		double oldPlaneX = ge->plane.x;
		ge->plane.x = ge->plane.x * cos(ge->rotSpeed) - ge->plane.y * sin(ge->rotSpeed);
		ge->plane.y = oldPlaneX * sin(ge->rotSpeed) + ge->plane.y * cos(ge->rotSpeed);
	}
	if(keycode == KEY_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = ge->dir.x;
		ge->dir.x = ge->dir.x * cos(-ge->rotSpeed) - ge->dir.y * sin(-ge->rotSpeed);
		ge->dir.y = oldDirX * sin(-ge->rotSpeed) + ge->dir.y * cos(-ge->rotSpeed);
		double oldPlaneX = ge->plane.x;
		ge->plane.x = ge->plane.x * cos(-ge->rotSpeed) - ge->plane.y * sin(-ge->rotSpeed);
		ge->plane.y = oldPlaneX * sin(-ge->rotSpeed) + ge->plane.y * cos(-ge->rotSpeed);
	}
	draw(ge);

	return 0;
}

int 	main()
{
	GameEngine ge;
	//void		*img;

	ge.moveSpeed = 0.1; //the constant value is in squares/second
	ge.rotSpeed = 0.02; //the constant value is in radians/second
	ge.pl.pos.x = 22;
	ge.pl.pos.y = 12;  //x and y start position
	ge.dir.x = -1;
	ge.dir.y = 0; //initial direction vector
	ge.plane.x = 0;
	ge.plane.y = 0.66; //the 2d raycaster version of camera plane
	int h,w;
	h = 0;
	w = 0;
	
	//generate some textures
	for(int i=0; i<8; i++)
	{
		texture[i] = (int *)malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
	}

	for(int x = 0; x < TEX_WIDTH; x++)
	{
		for(int y = 0; y < TEX_HEIGHT; y++)
		{
			int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / TEX_HEIGHT;
			int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
			texture[0][y * TEX_WIDTH + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); //flat red texture with black cross
			texture[1][y * TEX_WIDTH + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][y * TEX_WIDTH + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][y * TEX_WIDTH + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][y * TEX_WIDTH + x] = 256 * xorcolor; //xor green
			texture[5][y * TEX_WIDTH + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][y * TEX_WIDTH + x] = 65536 * ycolor; //red gradient
			texture[7][y * TEX_WIDTH + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}

	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	if ((mlx_win = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster")) == NULL)
		return (0);

	// img = mlx_xpm_file_to_image(mlx_ptr, "/Users/Morgan/Dropbox/42/work/cub3d/srcs/playground/eagle.xpm", &w, &h);
	// printf("w : %d h : %d p : %p", w, h, img);
	// getchar();
	
	mlx_loop_hook(mlx_ptr, &draw, &ge);
	mlx_key_hook(mlx_win, &key_hook, &ge);
	mlx_hook(mlx_win, X11_KEY_PRESS, X11_KEY_PRESS_M, &key_hook, &ge);
	mlx_hook(mlx_win, X11_KEY_RELEASE, X11_KEY_RELEASE_M, &key_hook, &ge);
	mlx_loop(mlx_ptr);

}