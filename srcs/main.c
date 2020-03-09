/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:36:45 by mroux             #+#    #+#             */
/*   Updated: 2020/03/09 19:14:56 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(int r)
{
	ft_printf("Erreur à la lecture du fichier cub : %d", r);
}

int		init_engine(t_game_engine *ge)
{
	ge->move_speed = 0.1;
	ge->rot_speed = 0.06;
	ge->keys = NONE;
	return (1);
}

void	save(t_game_engine *ge)
{
	t_img			img;

	if (draw_world(ge, &img) == ERROR)
	{
		print_error(ERROR);
		return ;
	}
	if (img_to_bmp(&img, "./res/test.bmp") == ERROR)
		print_error(ERROR);
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
	int				r;

	if ((ge.mlx_ptr = mlx_init()) == NULL)
		return (0);
	if (argc < 2)
		return (0);
	if ((r = load_cub_file(&ge, argv[1])) != OK)
	{
		print_error(r);
		return (0);
	}
	init_engine(&ge);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		save(&ge);
	else if (argc == 2)
	{
		if ((ge.mlx_win = mlx_new_window(ge.mlx_ptr, ge.screen_w,
									ge.screen_h, "Raycaster")) == NULL)
			return (0);
		set_hooks(&ge);
		mlx_loop(ge.mlx_ptr);
	}
	return (0);
}
