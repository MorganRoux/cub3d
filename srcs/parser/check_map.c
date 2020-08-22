/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:40:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 16:48:36 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_player_dir(t_ge *ge, int i)
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
	return (OK);
}

int		init_player(t_ge *ge, size_t i)
{
	if (init_player_dir(ge, i))
		return (ERROR);
	ge->map.p_map[i] = 0;
	ge->plane.x = -ge->dir.y * 0.66;
	ge->plane.y = ge->dir.x * 0.66;
	ge->pl.pos.x = i % ge->map.w + 0.5;
	ge->pl.pos.y = i / ge->map.w + 0.5;
	if ((ge->map.flags & FLAG_PLAYER) == FLAG_PLAYER)
		return (ERROR);
	else
		ge->map.flags = ge->map.flags | FLAG_PLAYER;
	return (OK);
}

int		init_sprite(t_ge *ge, size_t i)
{
	int	*nsprite;

	nsprite = &ge->map.n_sprite;
	ge->map.sprites = ft_realloc(ge->map.sprites, *nsprite * sizeof(t_sprite),
								(*nsprite + 1) * sizeof(t_sprite));
	ge->map.sprites[*nsprite].pos.x = i % ge->map.w + 0.5;
	ge->map.sprites[*nsprite].pos.y = i / ge->map.w + 0.5;
	ge->map.sprites[*nsprite].texture = ge->map.sprite_ref.texture;
	*nsprite = *nsprite + 1;
	getchar();
	return (OK);
}

int		check_map(t_ge *ge)
{
	size_t	i;

	i = 0;
	ge->map.n_sprite = 0;
	while (i < ge->map.size - 1)
	{
		if (ge->map.p_map[i] == 8)
			ge->map.p_map[i] = 0;
		if (ge->map.p_map[i] == 9)
			ge->map.p_map[i] = 2;
		if (ge->map.p_map[i] > 9)
			if (init_player(ge, i) == ERROR)
				return (ERROR);
		if (ge->map.p_map[i] == 2)
		{
			if (init_sprite(ge, i) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (OK);
}
