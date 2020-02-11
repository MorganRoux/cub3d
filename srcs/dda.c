#include "cub3d.h"

extern int worldMap[MAP_HEIGHT * MAP_WIDTH];

void	init_dda(s_dda *dda, int n, GameEngine *ge)
{
	//calculate ray position and direction
	dda->cameraX = 2 * n / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
	dda->rayDirX = ge->dir.x + ge->plane.x * dda->cameraX;
	dda->rayDirY = ge->dir.y + ge->plane.y * dda->cameraX;
	//which box of the map we're in
	dda->mapX = (int)(ge->pl.pos.x);
	dda->mapY = (int)(ge->pl.pos.y);
	dda->deltaDistX = fabs(1 / dda->rayDirX); //sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
	dda->deltaDistY = fabs(1 / dda->rayDirY); //sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
	dda->stepX = (dda->rayDirX < 0) ? -1 : 1;
	dda->sideDistX = (dda->rayDirX < 0) ? (ge->pl.pos.x - dda->mapX) * dda->deltaDistX : 
					(dda->mapX + 1.0 - ge->pl.pos.x) * dda->deltaDistX;
	dda->stepY = (dda->rayDirY < 0) ? -1 : 1;
	dda->sideDistY = (dda->rayDirY < 0) ? (ge->pl.pos.y - dda->mapY) * dda->deltaDistY : (dda->mapY + 1.0 - ge->pl.pos.y) * dda->deltaDistY;
}

int	detect_collision(s_dda *dda)
{
	int	hit;
	int	side; //was a NS or a EW wall hit?

	hit = 0;
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if(dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			side = 0;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if(worldMap[dda->mapY * MAP_WIDTH + dda->mapX] > 0) 
			hit = 1;
	}
	return (side);
}

int	get_line_height(s_dda *dda, int side, GameEngine *ge)
{
	int		tex_x;
	double	perpWallDist;
	int		lineHeight;
	double	wall_x;

	perpWallDist = (side == 0) ? (dda->mapX - ge->pl.pos.x + (1 - dda->stepX) / 2) / dda->rayDirX : 
									(dda->mapY - ge->pl.pos.y + (1 - dda->stepY) / 2) / dda->rayDirY;
	lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
	dda->drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
	dda->drawStart = (dda->drawStart < 0) ? 0 : dda->drawStart;
	dda->drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
	dda->drawEnd = (dda->drawEnd >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - 1 : dda->drawEnd;
	wall_x = (side == 0) ? ge->pl.pos.y + perpWallDist * dda->rayDirY :
								ge->pl.pos.x + perpWallDist * dda->rayDirX;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)(TEX_WIDTH));
	if(side == 0 && dda->rayDirX > 0) 
		tex_x = TEX_WIDTH - tex_x - 1;
	if(side == 1 && dda->rayDirY < 0) 
		tex_x = TEX_WIDTH - tex_x - 1;
	return tex_x;
}

int		compute_dda(s_dda *dda, int n, GameEngine *ge)
{

	int	side;
	int tex_x;

	init_dda(dda, n, ge);
	side = detect_collision(dda);
	tex_x = get_line_height(dda, side, ge);
	return tex_x;
}