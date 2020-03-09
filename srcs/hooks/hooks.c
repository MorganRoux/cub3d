/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:03:54 by mroux             #+#    #+#             */
/*   Updated: 2020/03/09 19:19:34 by mroux            ###   ########.fr       */
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
		move_left(ge);
	if ((ge->keys & RIGHT) != 0)
		move_right(ge);
	if ((ge->keys & ROT_L) != 0)
		rot_left(ge);
	if ((ge->keys & ROT_R) != 0)
		rot_right(ge);
	if (draw(ge) == ERROR)
		exit_hook(ge);
	return (0);
}

int		key_hook_press(int keycode, void *param)
{
	t_game_engine *ge;

	ge = (t_game_engine *)param;
	if (keycode == KEY_W)
		ge->keys = ge->keys | UP;
	else if (keycode == KEY_S)
		ge->keys = ge->keys | DOWN;
	else if (keycode == KEY_A)
		ge->keys = ge->keys | LEFT;
	else if (keycode == KEY_D)
		ge->keys = ge->keys | RIGHT;
	else if (keycode == KEY_LEFT)
		ge->keys = ge->keys | ROT_L;
	else if (keycode == KEY_RIGHT)
		ge->keys = ge->keys | ROT_R;
	else if (keycode == KEY_ESCAPE)
		exit_hook(ge);
	return (0);
}

int		key_hook_release(int keycode, void *param)
{
	t_game_engine *ge;

	ge = (t_game_engine *)param;
	if (keycode == KEY_W)
		ge->keys = ge->keys & ~UP;
	else if (keycode == KEY_S)
		ge->keys = ge->keys & ~DOWN;
	else if (keycode == KEY_A)
		ge->keys = ge->keys & ~LEFT;
	else if (keycode == KEY_D)
		ge->keys = ge->keys & ~RIGHT;
	else if (keycode == KEY_LEFT)
		ge->keys = ge->keys & ~ROT_L;
	else if (keycode == KEY_RIGHT)
		ge->keys = ge->keys & ~ROT_R;
	return (0);
}

int		exit_hook(t_game_engine *ge)
{
	mlx_destroy_window(ge->mlx_ptr, ge->mlx_win);
	exit(0);
	return (0);
}
