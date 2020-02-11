#include "cub3d.h"

extern int worldMap[MAP_HEIGHT][MAP_WIDTH];

void	move_front(GameEngine *ge)
{
	if(worldMap[(int)(ge->pl.pos.y)][(int)(ge->pl.pos.x + ge->dir.x * ge->moveSpeed)] == 0) 
			ge->pl.pos.x += ge->dir.x * ge->moveSpeed;
	if(worldMap[(int)(ge->pl.pos.y + ge->dir.y * ge->moveSpeed)][(int)(ge->pl.pos.x)] == 0) 
		ge->pl.pos.y += ge->dir.y * ge->moveSpeed;
}

void	move_back(GameEngine *ge)
{
	if(worldMap[(int)(ge->pl.pos.y)][(int)(ge->pl.pos.x - ge->dir.x * ge->moveSpeed)] == 0) 
			ge->pl.pos.x -= ge->dir.x * ge->moveSpeed;
	if(worldMap[(int)(ge->pl.pos.y - ge->dir.y * ge->moveSpeed)][(int)(ge->pl.pos.x)] == 0) 
		ge->pl.pos.y -= ge->dir.y * ge->moveSpeed;
}

void	rot_left(GameEngine *ge)
{
	//both camera direction and camera plane must be rotated
	double oldDirX = ge->dir.x;
	ge->dir.x = ge->dir.x * cos(ge->rotSpeed) - ge->dir.y * sin(ge->rotSpeed);
	ge->dir.y = oldDirX * sin(ge->rotSpeed) + ge->dir.y * cos(ge->rotSpeed);
	double oldPlaneX = ge->plane.x;
	ge->plane.x = ge->plane.x * cos(ge->rotSpeed) - ge->plane.y * sin(ge->rotSpeed);
	ge->plane.y = oldPlaneX * sin(ge->rotSpeed) + ge->plane.y * cos(ge->rotSpeed);
}

void	rot_right(GameEngine *ge)
{
	//both camera direction and camera plane must be rotated
	double oldDirX = ge->dir.x;
	ge->dir.x = ge->dir.x * cos(-ge->rotSpeed) - ge->dir.y * sin(-ge->rotSpeed);
	ge->dir.y = oldDirX * sin(-ge->rotSpeed) + ge->dir.y * cos(-ge->rotSpeed);
	double oldPlaneX = ge->plane.x;
	ge->plane.x = ge->plane.x * cos(-ge->rotSpeed) - ge->plane.y * sin(-ge->rotSpeed);
	ge->plane.y = oldPlaneX * sin(-ge->rotSpeed) + ge->plane.y * cos(-ge->rotSpeed);
}