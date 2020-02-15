
#include <mlx.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>

#include "libftprintf.h"
#include "get_next_line.h"
#include "keys.h"

// #define MAP_WIDTH 24
// #define MAP_HEIGHT 24
// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define BYTES_PER_PIXELS 3
#define TEX_DIR "/Users/mroux/42Cursus/cub3d/repo/srcs/playground/"
#define ERROR -1
#define	OK 0

typedef struct	vect
{
	double x;
	double y;
}				s_vect;

typedef struct	pxl_color
{
	int r;
	int v;
	int	b;
}				s_color;

typedef	struct	image
{
	void	*p_img;
	char	*data;
	int		h;
	int		w;
	int		size_line;
	int		bits_per_pixels;
	int		endian;
	char	*path;
}				s_img;

typedef struct	world_map
{
/*
** 	Textures ; NO, SO, EA, WE
** 	Colors : Floor, ceil
*/
	char	*p_map;
	int		w;
	int		h;
	s_img	textures[8];
	s_color	color[2];
	s_img	sprite;
}				s_map;

typedef struct	player
{
	s_vect	pos;
}				s_player;

typedef struct	game_engine
{
	void		*mlx_ptr;
	void		*mlx_win;
	char		*map;
	s_map		smap;
	//s_img		textures[8];
	double		moveSpeed;
	double		rotSpeed;
	s_vect		dir;
	s_vect		plane;
	s_player	pl;
	int			screen_w;
	int			screen_h;
}				GameEngine;

typedef struct DDA
{
	int		drawStart;
	int		drawEnd;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	rayDirX;
	double	rayDirY;
	double	cameraX;
	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;
}				s_dda;

int		initEngine(GameEngine *ge);

void	init_dda(s_dda *dda, int n, GameEngine *ge);
int		detect_collision(s_dda *dda, GameEngine *ge);
int		compute_dda(s_dda *dda, int n, GameEngine *ge);

void	move_front(GameEngine *ge);
void	move_back(GameEngine *ge);
void	rot_left(GameEngine *ge);
void	rot_right(GameEngine *ge);

int		key_hook(int keycode,void *param);
int		main_hook(void *param);

int		compute_fps();
int		img_vertline_put(int img_x, s_dda *dda, GameEngine *ge,
						s_img *tex, int tex_x, s_img *img);
int		draw(void *param);

int		load_cub_file(GameEngine *ge, char *path);
int		load_map_dimensions(GameEngine *ge, char *line);
int		load_colors(GameEngine *ge, char *line);
int		load_sprite(GameEngine *ge, char *line);
int		load_map(GameEngine *ge, int fd, char *line);
int		load_textures(GameEngine *ge, char *line);

int check_map(char *map);