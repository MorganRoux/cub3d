/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:36:45 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 18:18:11 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(int r)
{
	ft_printf("Error\nErreur à la lecture du fichier cub : %d", r);
}

void	save(t_ge *ge)
{
	t_img			img;

	if (draw_world(ge, &img) == ERROR)
	{
		print_error(ERROR);
		return ;
	}
	draw_sprite(ge, &img);
	if (img_to_bmp(&img, "./res/test.bmp") == ERROR)
		print_error(ERROR);
}

void	set_hooks(t_ge *ge)
{
	mlx_loop_hook(ge->mlx_ptr, &main_hook, ge);
	mlx_hook(ge->mlx_win, X11_KEY_PRESS, X11_KEY_PRESS_M, &key_hook_press, ge);
	mlx_hook(ge->mlx_win, 33, 0, &exit_hook, ge);
	mlx_hook(ge->mlx_win, X11_KEY_RELEASE, X11_KEY_RELEASE_M,
			&key_hook_release, ge);
}

int		init_main(t_ge *ge, int argc, char *argv[])
{
	int	r;

	if ((ge->mlx_ptr = mlx_init()) == NULL)
		return (ERROR);
	if (argc < 2)
		return (ERROR);
	if ((r = load_cub_file(ge, argv[1])) != OK)
	{
		print_error(r);
		return (ERROR);
	}
	init_engine(ge);
	if (init_dda(ge) == ERROR)
		return (ERROR);
	return (OK);
}

int		main(int argc, char *argv[])
{
	t_ge	ge;

	if (init_main(&ge, argc, argv) == ERROR)
		return (ERROR);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		save(&ge);
	else if (argc == 2)
	{
		if ((ge.mlx_win = mlx_new_window(ge.mlx_ptr, ge.screen_w,
									ge.screen_h, "Cub3D")) == NULL)
			return (0);
		set_hooks(&ge);
		mlx_loop(ge.mlx_ptr);
	}
	return (0);
}
