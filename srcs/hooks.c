/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:03:54 by mroux             #+#    #+#             */
/*   Updated: 2020/02/18 14:41:41 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_hook(void *param)
{
	t_game_engine *ge;

	ge = (t_game_engine *)param;
	if ((ge->keys & UP) != 0)
		move_front(ge);
	if ((ge->keys & DOWN) != 0)
		move_back(ge);
	if ((ge->keys & LEFT) != 0)
		rot_left(ge);
	if ((ge->keys & RIGHT) != 0)
		rot_right(ge);
	draw(ge);
	return (0);
}

int		key_hook_press(int keycode, void *param)
{
	t_game_engine *ge;
	
	ge = (t_game_engine *)param;
	if (keycode == KEY_UP)
		ge->keys = ge->keys | UP;
	else if (keycode == KEY_DOWN)
		ge->keys = ge->keys | DOWN;
	else if (keycode == KEY_LEFT)
		ge->keys = ge->keys | LEFT;
	else if (keycode == KEY_RIGHT)
		ge->keys = ge->keys | RIGHT;
	return (0);
}

int		key_hook_release(int keycode, void *param)
{
	t_game_engine *ge;
	
	ge = (t_game_engine *)param;
	if (keycode == KEY_UP)
		ge->keys = ge->keys & ~UP;
	else if (keycode == KEY_DOWN)
		ge->keys = ge->keys & ~DOWN;
	else if (keycode == KEY_LEFT)
		ge->keys = ge->keys & ~LEFT;
	else if (keycode == KEY_RIGHT)
		ge->keys = ge->keys & ~RIGHT;
	main_hook(param);
	return (0);
}

int		key_hook(int keycode, void *param)
{
	t_game_engine *ge;
	(void)keycode;
	ge = (t_game_engine *)param;
	// if ((ge->keys & KEY_UP) != 0)
	// 	move_front(ge);
	// if ((ge->keys & KEY_DOWN) != 0)
	// 	move_back(ge);
	// if ((ge->keys & KEY_LEFT) != 0)
	// 	rot_left(ge);
	// if ((ge->keys & KEY_RIGHT) != 0)
	// 	rot_right(ge);
	draw(ge);
	return (0);
}
