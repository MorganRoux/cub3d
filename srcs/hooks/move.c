/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:42:58 by mroux             #+#    #+#             */
/*   Updated: 2020/03/04 15:04:02 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_front(t_game_engine *ge)
{
	char	*world_map;
	double	new_x;
	double	new_y;

	new_x = ge->pl.pos.x + ge->dir.x * ge->move_speed;
	new_y = ge->pl.pos.y + ge->dir.y * ge->move_speed;
	world_map = ge->map.p_map;
	if (world_map[(int)(ge->pl.pos.y) * ge->map.w + (int)new_x] == 0)
		ge->pl.pos.x = new_x;
	if (world_map[(int)new_y * ge->map.w + (int)(ge->pl.pos.x)] == 0)
		ge->pl.pos.y = new_y;
}

void	move_back(t_game_engine *ge)
{
	char	*world_map;
	double	new_x;
	double	new_y;

	new_x = ge->pl.pos.x - ge->dir.x * ge->move_speed;
	new_y = ge->pl.pos.y - ge->dir.y * ge->move_speed;
	world_map = ge->map.p_map;
	if (world_map[(int)(ge->pl.pos.y) * ge->map.w + (int)new_x] == 0)
		ge->pl.pos.x = new_x;
	if (world_map[(int)new_y * ge->map.w + (int)(ge->pl.pos.x)] == 0)
		ge->pl.pos.y = new_y;
}

void	move_right(t_game_engine *ge)
{
	char	*world_map;
	double	new_x;
	double	new_y;

	new_x = ge->pl.pos.x - ge->dir.y * ge->move_speed;
	new_y = ge->pl.pos.y + ge->dir.x * ge->move_speed;
	world_map = ge->map.p_map;
	if (world_map[(int)(ge->pl.pos.y) * ge->map.w + (int)new_x] == 0)
		ge->pl.pos.x = new_x;
	if (world_map[(int)new_y * ge->map.w + (int)(ge->pl.pos.x)] == 0)
		ge->pl.pos.y = new_y;
}

void	move_left(t_game_engine *ge)
{
	char	*world_map;
	double	new_x;
	double	new_y;

	new_x = ge->pl.pos.x + ge->dir.y * ge->move_speed;
	new_y = ge->pl.pos.y - ge->dir.x * ge->move_speed;
	world_map = ge->map.p_map;
	if (world_map[(int)(ge->pl.pos.y) * ge->map.w + (int)new_x] == 0)
		ge->pl.pos.x = new_x;
	if (world_map[(int)new_y * ge->map.w + (int)(ge->pl.pos.x)] == 0)
		ge->pl.pos.y = new_y;
}
