/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:42:58 by mroux             #+#    #+#             */
/*   Updated: 2020/02/15 15:08:39 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_front(GameEngine *ge)
{
	char		*world_map;
	double	new_x;
	double	new_y;

	new_x = ge->pl.pos.x + ge->dir.x * ge->moveSpeed;
	new_y = ge->pl.pos.y + ge->dir.y * ge->moveSpeed;
	world_map = ge->smap.p_map;
	if (world_map[(int)(ge->pl.pos.y) * ge->smap.w + (int)new_x] == 0)
		ge->pl.pos.x = new_x;
	if (world_map[(int)new_y * ge->smap.w + (int)(ge->pl.pos.x)] == 0)
		ge->pl.pos.y = new_y;
}

void	move_back(GameEngine *ge)
{
	char		*world_map;
	double	new_x;
	double	new_y;

	new_x = ge->pl.pos.x - ge->dir.x * ge->moveSpeed;
	new_y = ge->pl.pos.y - ge->dir.y * ge->moveSpeed;
	world_map = ge->smap.p_map;
	if (world_map[(int)(ge->pl.pos.y) * ge->smap.w + (int)new_x] == 0)
		ge->pl.pos.x = new_x;
	if (world_map[(int)new_y * ge->smap.w + (int)(ge->pl.pos.x)] == 0)
		ge->pl.pos.y = new_y;
}

void	rot_left(GameEngine *ge)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = ge->dir.x;
	oldplane_x = ge->plane.x;
	ge->dir.x = ge->dir.x * cos(ge->rotSpeed) - ge->dir.y * sin(ge->rotSpeed);
	ge->dir.y = olddir_x * sin(ge->rotSpeed) + ge->dir.y * cos(ge->rotSpeed);
	ge->plane.x = ge->plane.x * cos(ge->rotSpeed) -
					ge->plane.y * sin(ge->rotSpeed);
	ge->plane.y = oldplane_x * sin(ge->rotSpeed) +
					ge->plane.y * cos(ge->rotSpeed);
}

void	rot_right(GameEngine *ge)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = ge->dir.x;
	oldplane_x = ge->plane.x;
	ge->dir.x = ge->dir.x * cos(-ge->rotSpeed) - ge->dir.y * sin(-ge->rotSpeed);
	ge->dir.y = olddir_x * sin(-ge->rotSpeed) + ge->dir.y * cos(-ge->rotSpeed);
	ge->plane.x = ge->plane.x * cos(-ge->rotSpeed) -
					ge->plane.y * sin(-ge->rotSpeed);
	ge->plane.y = oldplane_x * sin(-ge->rotSpeed) +
					ge->plane.y * cos(-ge->rotSpeed);
}
