/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:40:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/04 14:54:10 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game_engine *ge, char dir, size_t pos)
{
	(void)pos;
	(void)dir;
	(void)ge;
	// if (dir + '0' == 'N')
	// {
	// 	ge->dir.x = 0;
	// 	ge->dir.y = -1;
	// }
	// else if (dir + '0' == 'S')
	// {
	// 	ge->dir.x = 0;
	// 	ge->dir.y = 1;
	// }
	// else if (dir + '0' == 'O')
	// {
	// 	ge->dir.x = -1;
	// 	ge->dir.y = 0;
	// }
	// else if (dir + '0' == 'E')
	// {
	// 	ge->dir.x = 1;
	// 	ge->dir.y = 0;
	// }
	printf("stop");
	getchar();
	ge->dir.x = -1;
	ge->dir.y = 0;
	ge->plane.x = ge->dir.y * 0.66;
	ge->plane.y = -ge->dir.x * 0.66;
	ge->pl.pos.x = 2;
	ge->pl.pos.y = 2;
}

int		check_map(t_game_engine *ge)
{
	char	*map;
	size_t	i;
printf("%zu", ge->map.size);
	getchar();
	i = 0;
	map = ge->map.p_map;
	while (i < ge->map.size)
	{
		if (map[i] >= 9)
		{
			init_player(ge, map[i], i);
			map[i] = 0;
		}
		i++;
	}
	return (OK);
}
