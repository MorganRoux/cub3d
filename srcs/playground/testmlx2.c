#include "cub3d.h"

int		mlx_vertline_put(int x, int drawStart, int drawEnd, int color, void *mlx_ptr, void *mlx_win)
{
	int i;

	i = drawStart;
	while (i < drawEnd)
	{
		mlx_pixel_put(mlx_ptr, mlx_win, x, i, color);
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

int		draw(void *param)
{
	GameEngine *ge;

	ge = (GameEngine *)param;

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	int drawStart;
	int drawEnd;
	int lineHeight;
	int color;

	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;
	//length of ray from one x or y-side to next x or y-side
	double deltaDistX;
	double deltaDistY;
	double rayDirX;
	double rayDirY;
	double cameraX;
	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;
	//which box of the map we're in
	int mapX;
	int mapY;
	int side; //was a NS or a EW wall hit?
	int hit = 0; //was there a wall hit?
	double perpWallDist;
	
	mlx_clear_window ( mlx_ptr, mlx_win );
	for(int x = 0; x < SCREEN_WIDTH; x++)
	{
		//calculate ray position and direction
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
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

		//choose wall color
		
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0x00FF0000;    break; //red
			case 2:  color = 0x0000FF00;  break; //green
			case 3:  color = 0x000000FF;   break; //blue
			case 4:  color = 0x00FFFFFF;  break; //white
			default: color = 0X00FFFF00; break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1) 
			color = darken_color(color, 0.5);

		//draw the pixels of the stripe as a vertical line
		mlx_vertline_put(x, drawStart, drawEnd, color, mlx_ptr, mlx_win);
	}
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

	ge.moveSpeed = 0.1; //the constant value is in squares/second
	ge.rotSpeed = 0.10; //the constant value is in radians/second
	ge.pl.pos.x = 22;
	ge.pl.pos.y = 12;  //x and y start position
	ge.dir.x = -1;
	ge.dir.y = 0; //initial direction vector
	ge.plane.x = 0;
	ge.plane.y = 0.66; //the 2d raycaster version of camera plane
	
	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	if ((mlx_win = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster")) == NULL)
		return (0);

	mlx_loop_hook(mlx_ptr, &draw, &ge);
	mlx_key_hook(mlx_win, &key_hook, &ge);
	mlx_loop(mlx_ptr);

}