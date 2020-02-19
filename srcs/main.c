/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:36:45 by mroux             #+#    #+#             */
/*   Updated: 2020/02/19 17:39:24 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_engine(t_game_engine *ge)
{
	ge->move_speed = 0.1;
	ge->rot_speed = 0.06;
	ge->pl.pos.x = 2;
	ge->pl.pos.y = 2;
	ge->dir.x = -1;
	ge->dir.y = 0;
	ge->plane.x = 0;
	ge->plane.y = 0.66;
	ge->keys = NONE;
	return (1);
}

int		exit_hook(t_game_engine *ge)
{
	mlx_destroy_window(ge->mlx_ptr, ge->mlx_win);
	exit(0);
	return (0);
}

void	set_hooks(t_game_engine *ge)
{
	mlx_loop_hook(ge->mlx_ptr, &main_hook, ge);
	mlx_hook(ge->mlx_win, X11_KEY_PRESS, X11_KEY_PRESS_M, &key_hook_press, ge);
	mlx_hook(ge->mlx_win, 17, 0, &exit_hook, ge);
	mlx_hook(ge->mlx_win, X11_KEY_RELEASE, X11_KEY_RELEASE_M,
			&key_hook_release, ge);
}

int		main(int argc, char *argv[])
{
	t_game_engine	ge;

	init_engine(&ge);
	if ((ge.mlx_ptr = mlx_init()) == NULL)
		return (0);
	if (argc != 2)
		return (0);
	if (load_cub_file(&ge, argv[1]) < 0)
		return (0);
	if ((ge.mlx_win = mlx_new_window(ge.mlx_ptr, ge.screen_w,
									ge.screen_h, "Raycaster")) == NULL)
		return (0);
	set_hooks(&ge);
	mlx_loop(ge.mlx_ptr);
}
