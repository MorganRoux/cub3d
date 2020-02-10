#include "cub3d.h"

void	initEngine(GameEngine *ge)
{
	ge->moveSpeed = 0.1; //the constant value is in squares/second
	ge->rotSpeed = 0.06; //the constant value is in radians/second
	ge->pl.pos.x = 22;
	ge->pl.pos.y = 12;  //x and y start position
	ge->dir.x = -1;
	ge->dir.y = 0; //initial direction vector
	ge->plane.x = 0;
	ge->plane.y = 0.66; //the 2d raycaster version of camera plane
}

void	load_textures()
{
	int h,w;
	h = 0;
	w = 0;

	for(int i=0; i<8; i++)
	{
		int bpp, e;
		img2[i] = mlx_xpm_file_to_image(mlx_ptr, ft_strjoin(pics_dir,path[i]), &w, &h);
		//printf("w : %d h : %d p : %p", w, h, img2[i]);
		texture[i] = mlx_get_data_addr(img2[i], &bpp, &sl_tex, &e);//(int *)malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
	}
}

void	set_hooks(GameEngine *ge)
{
	mlx_loop_hook(mlx_ptr, &main_hook, &ge);
	mlx_key_hook(mlx_win, &key_hook, &ge);
	mlx_hook(mlx_win, X11_KEY_PRESS, X11_KEY_PRESS_M, &key_hook, &ge);
	mlx_hook(mlx_win, X11_KEY_RELEASE, X11_KEY_RELEASE_M, &key_hook, &ge);
}

int 	main()
{
	GameEngine ge;

	initGameEngine(ge);
	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	load_textures();
	if ((mlx_win = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster")) == NULL)
		return (0);
	set_hooks(&ge);
	mlx_loop(mlx_ptr);
}