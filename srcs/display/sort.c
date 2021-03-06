/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:55:22 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 15:31:38 by mroux            ###   ########.fr       */
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

void	sort_loop(int *sprite_order, double *sprite_distance, int n_sprite)
{
	char		continu;
	int			i;

	i = 0;
	continu = 1;
	while (continu)
	{
		continu = 0;
		i = 0;
		while (i < n_sprite - 1)
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

void	sort_sprite(t_ge *ge, int *sprite_order,
					double *sprite_distance)
{
	t_sprite	*sprite;
	int			i;

	i = 0;
	sprite = ge->map.sprites;
	while (i < ge->map.n_sprite)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((ge->pl.pos.x - sprite[i].pos.x)
				* (ge->pl.pos.x - sprite[i].pos.x)
				+ (ge->pl.pos.y - sprite[i].pos.y)
				* (ge->pl.pos.y - sprite[i].pos.y));
		i++;
	}
	sort_loop(sprite_order, sprite_distance, ge->map.n_sprite);
	i++;
}
