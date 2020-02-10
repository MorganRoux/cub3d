#include "cub3d.h"

int worldMap[MAP_HEIGHT][MAP_WIDTH]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

void		*mlx_ptr;
void		*mlx_win;

s_img		textures[8];
const char *tex_dir = "/Users/mroux/42Cursus/cub3d/repo/srcs/playground/";
char 		*tex_path[100] = {"eagle.xpm", "bluestone.xpm", "colorstone.xpm", "greystone.xpm", 
						"mossy.xpm", "purplestone.xpm", "redbrick.xpm", "wood.xpm"};

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

void	load_textures(s_img *tex, int n)
{
	int i;

	i = 0;
	while (i<n)
	{
		tex[i].p_img = mlx_xpm_file_to_image(mlx_ptr, ft_strjoin(tex_dir,tex_path[i]), &tex[i].w, &tex[i].h);
		tex[i].data = mlx_get_data_addr(tex[i].p_img, &tex[i].bits_per_pixels, &tex[i].size_line, &tex[i].endian);
		i++;
	}
}

void	set_hooks(GameEngine *ge)
{
	mlx_loop_hook(mlx_ptr, &main_hook, ge);
	mlx_key_hook(mlx_win, &key_hook, ge);
	mlx_hook(mlx_win, X11_KEY_PRESS, X11_KEY_PRESS_M, &key_hook, ge);
	mlx_hook(mlx_win, X11_KEY_RELEASE, X11_KEY_RELEASE_M, &key_hook, ge);
}

int 	main()
{
	GameEngine ge;

	initEngine(&ge);
	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	load_textures(textures, 8);
	if ((mlx_win = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster")) == NULL)
		return (0);
	set_hooks(&ge);
	mlx_loop(mlx_ptr);
}