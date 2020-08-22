/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:51:56 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 17:20:45 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			init_engine(t_ge *ge)
{
	ge->move_speed = 0.7;
	ge->rot_speed = 0.06;
	ge->keys = NONE;
	return (OK);
}

int			init_dda(t_ge *ge)
{
	if (!(ge->dda.z_buffer = malloc(sizeof(double) * ge->screen_w)))
		return (ERROR);
	if (!(ge->dda.sprite_order = (int *)malloc(sizeof(int) * ge->map.n_sprite)))
		return (ERROR);
	if (!(ge->dda.sprite_distance = (double *)malloc(
				sizeof(double) * ge->map.n_sprite)))
		return (ERROR);
	return (OK);
}
