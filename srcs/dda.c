/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:04:58 by mroux             #+#    #+#             */
/*   Updated: 2020/02/15 16:21:18 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(s_dda *dda, int n, GameEngine *ge)
{
	dda->camera_x = 2 * n / (double)ge->screen_w - 1;
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

int		detect_collision(s_dda *dda, GameEngine *ge)
{
	int	hit;
	int	side;
	char	*world_map;

	world_map = ge->smap.p_map;
	hit = 0;
	while (hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_x;
			dda->map_x += dda->step_x;
			side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_y;
			dda->map_y += dda->step_y;
			side = 1;
		}
		if (world_map[dda->map_y * ge->smap.w + dda->map_x] > 0)
			hit = 1;
	}
	return (side);
}

int		get_line_height(s_dda *dda, int side, GameEngine *ge)
{
	int		tex_x;
	double	perp_dist;
	int		line_height;
	double	wall_x;

	perp_dist = (side == 0) ?
		(dda->map_x - ge->pl.pos.x + (1 - dda->step_x) / 2) / dda->ray_dir_x :
		(dda->map_y - ge->pl.pos.y + (1 - dda->step_y) / 2) / dda->ray_dir_y;
	line_height = (int)(ge->screen_h / perp_dist);
	dda->draw_start = -line_height / 2 + ge->screen_h / 2;
	dda->draw_start = (dda->draw_start < 0) ? 0 : dda->draw_start;
	dda->draw_end = line_height / 2 + ge->screen_h / 2;
	dda->draw_end = (dda->draw_end >= ge->screen_h) ?
		ge->screen_h - 1 : dda->draw_end;
	wall_x = (side == 0) ? ge->pl.pos.y + perp_dist * dda->ray_dir_y :
								ge->pl.pos.x + perp_dist * dda->ray_dir_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)(TEX_WIDTH));
	if (side == 0 && dda->ray_dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (side == 1 && dda->ray_dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

int		compute_dda(s_dda *dda, int n, GameEngine *ge)
{
	int	side;
	int tex_x;

	init_dda(dda, n, ge);
	side = detect_collision(dda, ge);
	tex_x = get_line_height(dda, side, ge);
	return (tex_x);
}
