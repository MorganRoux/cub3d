
#include <mlx.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "libftprintf.h"
#include "keys.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define BYTES_PER_PIXELS 3
#define TEX_DIR "/Users/mroux/42Cursus/cub3d/repo/srcs/playground/"

typedef struct	vect
{
	double x;
	double y;
}				s_vect;

typedef struct	player
{
	s_vect	pos;
}				Player;

typedef	struct	image
{
	void	*p_img;
	char	*data;
	int		h;
	int		w;
	int		size_line;
	int		bits_per_pixels;
	int		endian;
}				s_img;

typedef struct	game_engine
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			*map;
	s_img		textures[8];
	double	moveSpeed;
	double	rotSpeed;
	s_vect	dir;
	s_vect	plane;
	s_vect	delta;
	s_vect	dist;
	Player	pl;
	double	d_alpha; 
	double	alpha[SCREEN_WIDTH];
}				GameEngine;

typedef struct DDA
{
	int		drawStart;
	int		drawEnd;
	//int		lineHeight;
	//length of ray from current position to next x or y-side
	double	sideDistX;
	double	sideDistY;
	//length of ray from one x or y-side to next x or y-side
	double	deltaDistX;
	double	deltaDistY;
	double	rayDirX;
	double	rayDirY;
	double	cameraX;
	//what direction to step in x or y-direction (either +1 or -1)
	int		stepX;
	int		stepY;
	//which box of the map we're in
	int		mapX;
	int		mapY;
	//double	perpWallDist;
	//double	wallX; //where exactly the wall was hit
}				s_dda;

void	initEngine(GameEngine *ge);

void	init_dda(s_dda *dda, int n, GameEngine *ge);
int		detect_collision(s_dda *dda);
int		compute_dda(s_dda *dda, int n, GameEngine *ge);

void	move_front(GameEngine *ge);
void	move_back(GameEngine *ge);
void	rot_left(GameEngine *ge);
void	rot_right(GameEngine *ge);

int		key_hook(int keycode,void *param);
int		main_hook(void *param);

int		compute_FPS();
int		img_vertline_put(int img_x, int drawStart, int drawEnd, s_img *tex, int tex_x, s_img *img);
int		draw(void *param);