/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:55:22 by mroux             #+#    #+#             */
/*   Updated: 2020/03/09 19:13:22 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap(int *sprite_order, double *sprite_distance)
{
	double		temp;

	temp = sprite_distance[0];
	sprite_distance[0] = sprite_distance[1];
	sprite_distance[1] = temp;
	temp = sprite_order[0];
	sprite_order[0] = sprite_order[1];
	sprite_order[1] = (int)temp;
}

void	sort_loop(int *sprite_order, double *sprite_distance)
{
	char		continu;
	int			i;

	i = 0;
	continu = 1;
	while (continu)
	{
		continu = 0;
		while (i < SPRITE_NUMBER - 1)
		{
			if (sprite_distance[i] < sprite_distance[i + 1])
			{
				continu = 1;
				swap(&sprite_order[i], &sprite_distance[i]);
			}
			i++;
		}
	}
}

void	sort_sprite(t_game_engine *ge, int *sprite_order,
					double *sprite_distance)
{
	t_sprite	*sprite;
	int			i;

	i = 0;
	sprite = ge->map.sprite;
	while (i < SPRITE_NUMBER)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((ge->pl.pos.x - sprite[i].pos.x)
				* (ge->pl.pos.x - sprite[i].pos.x)
				+ (ge->pl.pos.y - sprite[i].pos.y)
				* (ge->pl.pos.y - sprite[i].pos.y));
		i++;
	}
	sort_loop(sprite_order, sprite_distance);
	i++;
}
