#include "cub3d.h"
#include <stdio.h>

int		img_vertline_put(int img_line, int drawStart, int drawEnd, char *tex, int texX, char *img_data)
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
		for (int k =0; k<4;k++)
				img_data[i * size_line + img_line*b + k] = tex[texY * sl_tex + texX*b + k]; 
		i++;
	}
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

	//Compute FPS
    double cpu_time_used;
    int FPS;
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	FPS = 1.0 / cpu_time_used;
	mlx_string_put(mlx_ptr, mlx_win, 0,20,0x00FFFFFF, ft_strjoin("FPS", ft_itoa(FPS)));
	start = clock();

	return 0;
}