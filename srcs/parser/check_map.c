/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:40:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/10 15:35:51 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_player(t_game_engine *ge, size_t i)
{
	if (ge->map.p_map[i] + '0' == 'N')
	{
		ge->dir.x = 0;
		ge->dir.y = -1;
	}
	else if (ge->map.p_map[i] + '0' == 'S')
	{
		ge->dir.x = 0;
		ge->dir.y = 1;
	}
	else if (ge->map.p_map[i] + '0' == 'O')
	{
		ge->dir.x = -1;
		ge->dir.y = 0;
	}
	else if (ge->map.p_map[i] + '0' == 'E')
	{
		ge->dir.x = 1;
		ge->dir.y = 0;
	}
	else
		return (ERROR);
	if ((ge->map.flags & FLAG_PLAYER) == FLAG_PLAYER)
		return (ERROR);
	else
		ge->map.flags = ge->map.flags | FLAG_PLAYER;
	ge->map.p_map[i] = 0;
	ge->plane.x = -ge->dir.y * 0.66;
	ge->plane.y = ge->dir.x * 0.66;
	ge->pl.pos.x = i % ge->map.w + 0.5;
	ge->pl.pos.y = i / ge->map.w + 0.5;
	return (OK);
}

int		init_stripe(t_game_engine *ge, int *nsprite, size_t i)
{
	ge->map.sprite[*nsprite].pos.x = i % ge->map.w + 0.5;
	ge->map.sprite[*nsprite].pos.y = i / ge->map.w + 0.5;
	if (*nsprite < SPRITE_NUMBER - 1)
		*nsprite = *nsprite + 1;
	return (OK);
}

int		check_map(t_game_engine *ge)
{
	size_t	i;
	int		nsprite;

	i = 0;
	nsprite = 0;
	while (i < ge->map.size)
	{
		if (ge->map.p_map[i] >= 9)
			if (init_player(ge, i) == ERROR)
				return (ERROR);
		if (ge->map.p_map[i] == 2)
			if (init_stripe(ge, &nsprite, i) == ERROR)
				return (ERROR);
		i++;
	}
	return (OK);
}
