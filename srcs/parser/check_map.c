/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:40:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/05 10:54:54 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game_engine *ge, char *map, size_t i)
{
	if (map[i] + '0' == 'N')
	{
		ge->dir.x = 0;
		ge->dir.y = -1;
	}
	else if (map[i] + '0' == 'S')
	{
		ge->dir.x = 0;
		ge->dir.y = 1;
	}
	else if (map[i] + '0' == 'O')
	{
		ge->dir.x = -1;
		ge->dir.y = 0;
	}
	else if (map[i] + '0' == 'E')
	{
		ge->dir.x = 1;
		ge->dir.y = 0;
	}
	map[i] = 0;
	ge->plane.x = -ge->dir.y * 0.66;
	ge->plane.y = ge->dir.x * 0.66;
	ge->pl.pos.x = i % ge->map.w + 0.5;
	ge->pl.pos.y = i / ge->map.w + 0.5;
}

void	init_stripe(t_game_engine *ge, char *map, size_t i)
{
	ge->map.sprite[0].pos.x = i % ge->map.w + 0.5;
	ge->map.sprite[0].pos.y = i / ge->map.w + 0.5;
	(void)map;
}

int		check_map(t_game_engine *ge)
{
	char	*map;
	size_t	i;
	
	i = 0;
	map = ge->map.p_map;
	while (i < ge->map.size)
	{
		if (map[i] >= 9)
			init_player(ge, map, i);
		if (map[i] == 2)
			init_stripe(ge, map, i);
		i++;
	}
	return (OK);
}
