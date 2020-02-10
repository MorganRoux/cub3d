#include "cub3d.h"

extern void		*mlx_ptr;
extern void		*mlx_win;

extern s_img		textures[8];
extern const char *tex_dir;
extern char 		*tex_path[100];
extern int worldMap[MAP_HEIGHT][MAP_WIDTH];

int		main_hook(void *param)
{
	GameEngine *ge;

	ge = (GameEngine *)param;
	draw(ge);
	return 0;
}

int		key_hook(int keycode, void *param)
{
	GameEngine *ge;

	ge = (GameEngine *)param;
	if(keycode == KEY_UP)
		move_front(ge);
	else if(keycode == KEY_DOWN)
		move_back(ge);
	else if(keycode == KEY_LEFT)
		rot_left(ge);
	else if(keycode == KEY_RIGHT)
		rot_right(ge);
	draw(ge);
	return 0;
}