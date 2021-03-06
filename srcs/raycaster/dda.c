/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:04:58 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 16:52:58 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		update_dda(t_dda *dda, t_ge *ge)
{
	dda->camera_x = 2 * dda->img_x / (double)ge->screen_w - 1;
	dda->ray_dir_x = ge->dir.x + ge->plane.x * dda->camera_x;
	dda->ray_dir_y = ge->dir.y + ge->plane.y * dda->camera_x;
	dda->map_x = (int)(ge->pl.pos.x);
	dda->map_y = (int)(ge->pl.pos.y);
	dda->delta_x = fabs(1 / dda->ray_dir_x);
	dda->delta_y = fabs(1 / dda->ray_dir_y);
	dda->step_x = (dda->ray_dir_x < 0) ? -1 : 1;
	dda->side_dist_x = (dda->ray_dir_x < 0) ?
					(ge->pl.pos.x - dda->map_x) * dda->delta_x :
					(dda->map_x + 1.0 - ge->pl.pos.x) * dda->delta_x;
	dda->step_y = (dda->ray_dir_y < 0) ? -1 : 1;
	dda->side_dist_y = (dda->ray_dir_y < 0) ?
					(ge->pl.pos.y - dda->map_y) * dda->delta_y :
					(dda->map_y + 1.0 - ge->pl.pos.y) * dda->delta_y;
}

/*
**	find_wall_orientation()
**	find the texture to apply dependending on the cardinal
**	orientation
**	y = -1 : point to North
**	y = 1 ; point to South
**	x = 1 : point to East
**	x = -1 : point to West
**	side = 0 : hit along x => E-W
**	side = 1 : hit along y => S-N
*/

t_cardinal	get_wall_orientation(t_dda *dda)
{
	if (dda->side == 0)
		return ((dda->ray_dir_x >= 0) ? WE : EA);
	else
		return ((dda->ray_dir_y >= 0) ? NO : SO);
}

void		detect_collision(t_dda *dda, t_ge *ge)
{
	int		hit;
	char	*world_map;

	world_map = ge->map.p_map;
	hit = 0;
	while (hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (world_map[dda->map_y * ge->map.w + dda->map_x] == 1)
			hit = 1;
	}
}

/*
**	get_line_height
**	Compute height (in pxl) of the line to be drawn on screen
**	return column of the texture to be printed
**	perp_dist:	corrected dist to the wall by ray_dir (fisheye removed)
*/

int			get_line_height(t_dda *dda, t_ge *ge)
{
	double	perp_dist;
	double	wall_pos;

	perp_dist = (dda->side == 0) ?
		(dda->map_x - ge->pl.pos.x + (1 - dda->step_x) / 2) / dda->ray_dir_x :
		(dda->map_y - ge->pl.pos.y + (1 - dda->step_y) / 2) / dda->ray_dir_y;
	dda->line_height = (int)(ge->screen_h / perp_dist);
	dda->draw_start_y = -dda->line_height / 2 + ge->screen_h / 2;
	dda->draw_start_y = (dda->draw_start_y < 0) ? 0 : dda->draw_start_y;
	dda->draw_end_y = dda->line_height / 2 + ge->screen_h / 2;
	dda->draw_end_y = (dda->draw_end_y >= ge->screen_h) ?
		ge->screen_h - 1 : dda->draw_end_y;
	wall_pos = (dda->side == 0) ? ge->pl.pos.y + perp_dist * dda->ray_dir_y :
								ge->pl.pos.x + perp_dist * dda->ray_dir_x;
	wall_pos -= floor((wall_pos));
	dda->tex_x = (int)(wall_pos * (double)(TEX_WIDTH));
	if (dda->side == 0 && dda->ray_dir_x > 0)
		dda->tex_x = TEX_WIDTH - dda->tex_x - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		dda->tex_x = TEX_WIDTH - dda->tex_x - 1;
	dda->z_buffer[dda->img_x] = perp_dist;
	return (OK);
}

int			compute_dda(t_dda *dda, t_ge *ge)
{
	update_dda(dda, ge);
	detect_collision(dda, ge);
	get_line_height(dda, ge);
	return (OK);
}
