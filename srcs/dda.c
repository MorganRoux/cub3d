/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:04:58 by mroux             #+#    #+#             */
/*   Updated: 2020/02/15 15:15:01 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(s_dda *dda, int n, GameEngine *ge)
{
	dda->cameraX = 2 * n / (double)ge->screen_w - 1;
	dda->rayDirX = ge->dir.x + ge->plane.x * dda->cameraX;
	dda->rayDirY = ge->dir.y + ge->plane.y * dda->cameraX;
	dda->mapX = (int)(ge->pl.pos.x);
	dda->mapY = (int)(ge->pl.pos.y);
	dda->deltaDistX = fabs(1 / dda->rayDirX);
	dda->deltaDistY = fabs(1 / dda->rayDirY);
	dda->stepX = (dda->rayDirX < 0) ? -1 : 1;
	dda->sideDistX = (dda->rayDirX < 0) ?
					(ge->pl.pos.x - dda->mapX) * dda->deltaDistX :
					(dda->mapX + 1.0 - ge->pl.pos.x) * dda->deltaDistX;
	dda->stepY = (dda->rayDirY < 0) ? -1 : 1;
	dda->sideDistY = (dda->rayDirY < 0) ?
					(ge->pl.pos.y - dda->mapY) * dda->deltaDistY :
					(dda->mapY + 1.0 - ge->pl.pos.y) * dda->deltaDistY;
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
		if (dda->sideDistX < dda->sideDistY)
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
		if (world_map[dda->mapY * ge->smap.w + dda->mapX] > 0)
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
		(dda->mapX - ge->pl.pos.x + (1 - dda->stepX) / 2) / dda->rayDirX :
		(dda->mapY - ge->pl.pos.y + (1 - dda->stepY) / 2) / dda->rayDirY;
	line_height = (int)(ge->screen_h / perp_dist);
	dda->drawStart = -line_height / 2 + ge->screen_h / 2;
	dda->drawStart = (dda->drawStart < 0) ? 0 : dda->drawStart;
	dda->drawEnd = line_height / 2 + ge->screen_h / 2;
	dda->drawEnd = (dda->drawEnd >= ge->screen_h) ?
		ge->screen_h - 1 : dda->drawEnd;
	wall_x = (side == 0) ? ge->pl.pos.y + perp_dist * dda->rayDirY :
								ge->pl.pos.x + perp_dist * dda->rayDirX;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)(TEX_WIDTH));
	if (side == 0 && dda->rayDirX > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (side == 1 && dda->rayDirY < 0)
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
