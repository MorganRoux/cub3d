#include "cub3d.h"

int	initEngine(GameEngine *ge)
{
	int worldMap[MAP_HEIGHT * MAP_WIDTH]=
{
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7,
  4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7,
  4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
  4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,
  4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7,
  4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7,
  4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1,
  4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8,
  4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1,
  4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8,
  4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1,
  4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1,
  6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6,
  8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,
  6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6,
  4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3,
  4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2,
  4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2,
  4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2,
  4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2,
  4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2,
  4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2,
  4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2,
  4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3
};

	ge->moveSpeed = 0.1;
	ge->rotSpeed = 0.06;
	ge->pl.pos.x = 2;
	ge->pl.pos.y = 2;
	ge->dir.x = -1;
	ge->dir.y = 0;
	ge->plane.x = 0;
	ge->plane.y = 0.66;
	if (!(ge->map = (int *)malloc(sizeof(int) * MAP_HEIGHT * MAP_WIDTH)))
		return (0);
	for (int i=0; i < MAP_WIDTH * MAP_HEIGHT; i++)
		ge->map[i] = worldMap[i];
	return (1);
}

void	load_textures(GameEngine *ge, int n)
{
	int		i;
	s_img	*tex;
	char	*tex_path[100] = {"eagle.xpm", "bluestone.xpm", "colorstone.xpm", "greystone.xpm",
							"mossy.xpm", "purplestone.xpm", "redbrick.xpm", "wood.xpm"};

	i = 0;
	while (i < n)
	{
		tex = &ge->textures[i];
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
	initEngine(&ge);
	if ((ge.mlx_ptr = mlx_init()) == NULL)
		return (0);
	if (load_cub_file(&ge, argv[1]) < 0)
		return (0);
	load_textures(&ge, 8);
	if ((ge.mlx_win = mlx_new_window(ge.mlx_ptr, SCREEN_WIDTH,
									SCREEN_HEIGHT, "Raycaster")) == NULL)
		return (0);
	set_hooks(&ge);
	mlx_loop(ge.mlx_ptr);
}
