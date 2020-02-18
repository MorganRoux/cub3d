
#include <mlx.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>

#include "libftprintf.h"
#include "get_next_line.h"
#include "keys.h"

#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define BYTES_PER_PIXELS 3
#define TEX_DIR "/Users/mroux/42Cursus/cub3d/repo/srcs/playground/"
#define ERROR -1
#define	OK 0

typedef enum 
{
	NO = 0,
	SO = 1,
	EA = 2,
	WE = 3
}	t_cardinal;

/*
** 	Vector(2,1) : x, y
*/
typedef struct	t_vect
{
	double x;
	double y;
}				t_vect;

typedef struct	s_pxl_color
{
	int r;
	int v;
	int	b;
}				t_color;

/*
**	Represent an img in mlx with extra properties
**	p_imp : 			pointer to the mlx image
**	data : 				ptr to the pixel data
**	size_line : 		the number of bytes used to store 
**						one line of the image in memory
**	bits_per_pixels :	the depth of the image
**	path :				if provided, path on disk 
*/
typedef	struct	s_img
{
	void	*p_img;
	char	*data;
	int		h;
	int		w;
	int		size_line;
	int		bits_per_pxl;
	int		endian;
	char	*path;
}				t_img;

/*
**	Map properties 
**	p_map : 	ptr to the map
**	Textures : 	NO, SO, EA, WE
** 	colors : 	Floor, ceil
*/
typedef struct	world_map
{
	char	*p_map;
	int		w;
	int		h;
	t_img	textures[8];
	t_color	color[2];
	t_img	sprite;
}				s_map;

typedef struct	player
{
	t_vect	pos;
}				s_player;

/*
**	Game Engine properties
**	mlx_ptr :	use by mlx
**	mlx_win :	ptr to the screen
**	dir :		orientation of the player
**	plane :		orientation of the camera plane
*/
typedef struct	game_engine
{
	void		*mlx_ptr;
	void		*mlx_win;
	s_map		smap;
	double		moveSpeed;
	double		rotSpeed;
	t_vect		dir;
	t_vect		plane;
	s_player	pl;
	int			screen_w;
	int			screen_h;
}				GameEngine;

/*
**	Digital Differential Analysis algorithm
**	draw_start/end:	position on the screen of the column to be drawn
**	side_dist:	 	length of ray from current position to next x or y-side
**	delta:			length of ray from one x or y-side to next x or y-side 	
**	step:			what direction to step in x or y-direction (either +1 or -1)
**	camera_x:		pos on the camera plane. used to build ray_dir	
**	map:			which box of the map we're in	
*/
typedef struct s_dda
{
	int			draw_start;
	int			draw_end;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_x;
	double		delta_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		camera_x;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			line_height;
	int			side;
	t_cardinal	card;
}				t_dda;

int		init_engine(GameEngine *ge);

void	init_dda(t_dda *dda, int img_x, GameEngine *ge);
void	detect_collision(t_dda *dda, GameEngine *ge);
int		compute_dda(t_dda *dda, int img_x, GameEngine *ge);
t_cardinal	get_wall_orientation(t_dda *dda);

void	move_front(GameEngine *ge);
void	move_back(GameEngine *ge);
void	rot_left(GameEngine *ge);
void	rot_right(GameEngine *ge);

int		key_hook(int keycode,void *param);
int		main_hook(void *param);

int		compute_fps();
int		img_vertline_put(int img_x, t_dda *dda, GameEngine *ge,
						t_img *tex, int tex_x, t_img *img);
int		draw(void *param);

int		load_cub_file(GameEngine *ge, char *path);
int		load_map_dimensions(GameEngine *ge, char *line);
int		load_colors(GameEngine *ge, char *line);
int		load_sprite(GameEngine *ge, char *line);
int		load_map(GameEngine *ge, int fd, char *line);
int		load_textures(GameEngine *ge, char *line);

int check_map(char *map);