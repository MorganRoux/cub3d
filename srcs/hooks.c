/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:03:54 by mroux             #+#    #+#             */
/*   Updated: 2020/02/11 17:04:32 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_hook(void *param)
{
	GameEngine *ge;

	ge = (GameEngine *)param;
	draw(ge);
	return (0);
}

int		key_hook(int keycode, void *param)
{
	GameEngine *ge;

	ge = (GameEngine *)param;
	if (keycode == KEY_UP)
		move_front(ge);
	else if (keycode == KEY_DOWN)
		move_back(ge);
	else if (keycode == KEY_LEFT)
		rot_left(ge);
	else if (keycode == KEY_RIGHT)
		rot_right(ge);
	draw(ge);
	return (0);
}
