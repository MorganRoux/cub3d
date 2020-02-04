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
	(void)param;
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	int drawStart;
	int drawEnd;
	int lineHeight;
	int color;

	// while(!done())
	// {
		for(int x = 0; x < SCREEN_WIDTH; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)(posX);
			int mapY = (int)(posY);

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
			if(rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if(rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			//perform DDA
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
			if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

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
		// //timing for input and FPS counter
		// oldTime = time;
		// time = getTicks();
		// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		// print(1.0 / frameTime); //FPS counter
		// redraw();
		// cls();

		// //speed modifiers
		// double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		// double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
		// readKeys();
		// //move forward if no wall in front of you
		// if(keyDown(SDLK_UP))
		// {
		// 	if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		// 	if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
		// }
		// //move backwards if no wall behind you
		// if(keyDown(SDLK_DOWN))
		// {
		// 	if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		// 	if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		// }
		// //rotate to the right
		// if(keyDown(SDLK_RIGHT))
		// {
		// 	//both camera direction and camera plane must be rotated
		// 	double oldDirX = dirX;
		// 	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		// 	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		// 	double oldPlaneX = planeX;
		// 	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		// 	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		// }
		// //rotate to the left
		// if(keyDown(SDLK_LEFT))
		// {
		// 	//both camera direction and camera plane must be rotated
		// 	double oldDirX = dirX;
		// 	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		// 	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		// 	double oldPlaneX = planeX;
		// 	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		// 	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		// }
  //}
	return 0;
}

int 	main()
{
	
	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	if ((mlx_win = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster")) == NULL)
		return (0);

	mlx_loop_hook (mlx_ptr, &draw, NULL);
	mlx_loop(mlx_ptr);

}