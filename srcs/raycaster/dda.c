/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:04:58 by mroux             #+#    #+#             */
/*   Updated: 2020/02/19 16:29:13 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(t_dda *dda, int img_x, t_game_engine *ge)
{
	dda->camera_x = 2 * img_x / (double)ge->screen_w - 1;
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
		return ((dda->ray_dir_y >= 0) ? SO : NO);
	
}

void		detect_collision(t_dda *dda, t_game_engine *ge)
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
		if (world_map[dda->map_y * ge->map.w + dda->map_x] > 0)
			hit = 1;
	}
	get_wall_orientation(dda);
}

/*
**	get_line_height
**	Compute height (in pxl) of the line to be drawn on screen
**	return column of the texture to be printed
**	perp_dist:	corrected dist to the wall by ray_dir (fisheye removed)
**	
*/
int		get_line_height(t_dda *dda, t_game_engine *ge)
{
	int		tex_x;
	double	perp_dist;
	double	wall_pos;

	perp_dist = (dda->side == 0) ?
		(dda->map_x - ge->pl.pos.x + (1 - dda->step_x) / 2) / dda->ray_dir_x :
		(dda->map_y - ge->pl.pos.y + (1 - dda->step_y) / 2) / dda->ray_dir_y;
	dda->line_height = (int)(ge->screen_h / perp_dist);
	dda->draw_start = -dda->line_height / 2 + ge->screen_h / 2;
	dda->draw_start = (dda->draw_start < 0) ? 0 : dda->draw_start;
	dda->draw_end = dda->line_height / 2 + ge->screen_h / 2;
	dda->draw_end = (dda->draw_end >= ge->screen_h) ?
		ge->screen_h - 1 : dda->draw_end;
	wall_pos = (dda->side == 0) ? ge->pl.pos.y + perp_dist * dda->ray_dir_y :
								ge->pl.pos.x + perp_dist * dda->ray_dir_x;
	wall_pos -= floor((wall_pos));
	tex_x = (int)(wall_pos * (double)(TEX_WIDTH));
	if (dda->side == 0 && dda->ray_dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

int		compute_dda(t_dda *dda, int img_x, t_game_engine *ge)
{
	int tex_x;

	init_dda(dda, img_x, ge);
	detect_collision(dda, ge);
	tex_x = get_line_height(dda, ge);
	return (tex_x);
}
