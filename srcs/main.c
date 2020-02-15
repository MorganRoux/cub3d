#include "cub3d.h"

int	init_engine(GameEngine *ge)
{
	ge->moveSpeed = 0.1;
	ge->rotSpeed = 0.06;
	ge->pl.pos.x = 2;
	ge->pl.pos.y = 2;
	ge->dir.x = -1;
	ge->dir.y = 0;
	ge->plane.x = 0;
	ge->plane.y = 0.66;
	return (1);
}

void	load_tex(GameEngine *ge, int n)
{
	int		i;
	s_img	*tex;
	char	*tex_path[100] = {"eagle.xpm", "bluestone.xpm", "colorstone.xpm", "greystone.xpm",
							"mossy.xpm", "purplestone.xpm", "redbrick.xpm", "wood.xpm"};

	i = 0;
	while (i < n)
	{
		tex = &ge->smap.textures[i];
		tex->p_img = mlx_xpm_file_to_image(
						ge->mlx_ptr,
						ft_strjoin(TEX_DIR,tex_path[i]),
						&tex->w, &tex->h);
		tex->data = mlx_get_data_addr(
					tex->p_img, &tex->bits_per_pixels,
					&tex->size_line, &tex->endian);
		i++;
	}
}

void	set_hooks(GameEngine *ge)
{
	mlx_loop_hook(ge->mlx_ptr, &main_hook, ge);
	mlx_key_hook(ge->mlx_win, &key_hook, ge);
	mlx_hook(ge->mlx_win, X11_KEY_PRESS, X11_KEY_PRESS_M, &key_hook, ge);
	mlx_hook(ge->mlx_win, X11_KEY_RELEASE, X11_KEY_RELEASE_M, &key_hook, ge);
}

int		main(int argc, char *argv[])
{
	GameEngine	ge;
	init_engine(&ge);
	(void) argv;

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
