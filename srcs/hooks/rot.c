/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:32:21 by mroux             #+#    #+#             */
/*   Updated: 2020/03/04 15:04:11 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_right(t_game_engine *ge)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = ge->dir.x;
	oldplane_x = ge->plane.x;
	ge->dir.x = ge->dir.x * cos(ge->rot_speed) - ge->dir.y * sin(ge->rot_speed);
	ge->dir.y = olddir_x * sin(ge->rot_speed) + ge->dir.y * cos(ge->rot_speed);
	ge->plane.x = ge->plane.x * cos(ge->rot_speed) -
					ge->plane.y * sin(ge->rot_speed);
	ge->plane.y = oldplane_x * sin(ge->rot_speed) +
					ge->plane.y * cos(ge->rot_speed);
}

void	rot_left(t_game_engine *ge)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = ge->dir.x;
	oldplane_x = ge->plane.x;
	ge->dir.x = ge->dir.x * cos(-ge->rot_speed)
				- ge->dir.y * sin(-ge->rot_speed);
	ge->dir.y = olddir_x * sin(-ge->rot_speed)
				+ ge->dir.y * cos(-ge->rot_speed);
	ge->plane.x = ge->plane.x * cos(-ge->rot_speed)
				- ge->plane.y * sin(-ge->rot_speed);
	ge->plane.y = oldplane_x * sin(-ge->rot_speed)
				+ ge->plane.y * cos(-ge->rot_speed);
}
