#include "cub3d.h"
#include <stdio.h>

typedef struct s_dda
{
	int		drawStart;
	int		drawEnd;
	int		lineHeight;
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
	int		hit; //was there a wall hit?
	double	perpWallDist;
	double wallX; //where exactly the wall was hit
}				t_dda;


int		draw(void *param)
{
	GameEngine	*ge;
	t_img		img;	
	t_dda		dda;
	ge = (GameEngine *)param;

	//mlx_clear_window ( mlx_ptr, mlx_win );
	img.p_img = mlx_new_image (mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT );
	img.data = mlx_get_data_addr(img.p_img, &img.bits_per_pixels, &img.size_line, &img.endian);

	for(int n = 0; n < SCREEN_WIDTH; n++)
	{
		//calculate ray position and direction
		dda.cameraX = 2 * n / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
		dda.rayDirX = ge->dir.x + ge->plane.x * dda.cameraX;
		dda.rayDirY = ge->dir.y + ge->plane.y * dda.cameraX;
		//which box of the map we're in
		dda.mapX = (int)(ge->pl.pos.x);
		dda.mapY = (int)(ge->pl.pos.y);
		dda.deltaDistX = fabs(1 / dda.rayDirX); //sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		dda.deltaDistY = fabs(1 / dda.rayDirY); //sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

		//calculate step and initial sideDist
		if(dda.rayDirX < 0)
		{
			dda.stepX = -1;
			dda.sideDistX = (ge->pl.pos.x - dda.mapX) * dda.deltaDistX;
		}
		else
		{
			dda.stepX = 1;
			dda.sideDistX = (dda.mapX + 1.0 - ge->pl.pos.x) * dda.deltaDistX;
		}
		if(dda.rayDirY < 0)
		{
			dda.stepY = -1;
			dda.sideDistY = (ge->pl.pos.y - dda.mapY) * dda.deltaDistY;
		}
		else
		{
			dda.stepY = 1;
			dda.sideDistY = (dda.mapY + 1.0 - ge->pl.pos.y) * dda.deltaDistY;
		}
		//perform DDA
		dda.hit = 0;
		while (dda.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(dda.sideDistX < dda.sideDistY)
			{
				dda.sideDistX += dda.deltaDistX;
				dda.mapX += dda.stepX;
				dda.side = 0;
			}
			else
			{
				dda.sideDistY += dda.deltaDistY;
				dda.mapY += dda.stepY;
				dda.side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[dda.mapX][dda.mapY] > 0) 
				dda.hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(dda.side == 0) dda.perpWallDist = (dda.mapX - ge->pl.pos.x + (1 - dda.stepX) / 2) / dda.rayDirX;
		else          dda.perpWallDist = (dda.mapY - ge->pl.pos.y + (1 - dda.stepY) / 2) / dda.rayDirY;

		//Calculate height of line to draw on screen
		dda.lineHeight = (int)(SCREEN_HEIGHT / dda.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		dda.drawStart = -dda.lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(dda.drawStart < 0)dda.drawStart = 0;
		dda.drawEnd = dda.lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(dda.drawEnd >= SCREEN_HEIGHT)dda.drawEnd = SCREEN_HEIGHT - 1;
		
		if (dda.side == 0) dda.wallX = ge->pl.pos.y + dda.perpWallDist * dda.rayDirY;
		else           dda.wallX = ge->pl.pos.x + dda.perpWallDist * dda.rayDirX;
		dda.wallX -= floor((dda.wallX));

		//x coordinate on the texture
		int texX = (int)(dda.wallX * (double)(TEX_WIDTH));
		if(dda.side == 0 && dda.rayDirX > 0) texX = TEX_WIDTH - texX - 1;
		if(dda.side == 1 && dda.rayDirY < 0) texX = TEX_WIDTH - texX - 1;

		//draw the pixels of the stripe as a vertical line
		img_vertline_put(n, dda.drawStart, dda.drawEnd, &textures[worldMap[dda.mapX][dda.mapY] - 1], texX, &img);
	}
	
	mlx_put_image_to_window(mlx_ptr, mlx_win, img.p_img, 0, 0);
	mlx_string_put(mlx_ptr, mlx_win, 0, 20, 0x00FFFFFF, ft_strjoin("FPS", ft_itoa(compute_FPS())));
	return 0;
}