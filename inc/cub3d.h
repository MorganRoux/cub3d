/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:13:02 by mroux             #+#    #+#             */
/*   Updated: 2020/02/19 17:22:29 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>
# include "libftprintf.h"
# include "get_next_line.h"
# include "keys.h"
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define BYTES_PER_PIXELS 3
# define TEX_DIR "/Users/mroux/42Cursus/cub3d/repo/srcs/playground/"
# define ERROR -1
# define OK 0

typedef enum
{
	NO = 0,
	SO = 1,
	EA = 2,
	WE = 3
}	t_cardinal;

typedef enum
{
	NONE = 0,
	UP = 0b1,
	DOWN = 0b10,
	LEFT = 0b100,
	RIGHT = 0b1000,
	ROT_L = 0b10000,
	ROT_R = 0b100000,
}	t_keypress;

/*
** 	Vector(2,1) : x, y
*/
typedef struct	s_vect
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
typedef struct	s_world_map
{
	char	*p_map;
	int		w;
	int		h;
	t_img	textures[8];
	t_color	color[2];
	t_img	sprite;
}				t_map;

typedef struct	s_layer
{
	t_vect		pos;
}				t_player;

/*
**	Game Engine properties
**	mlx_ptr :	use by mlx
**	mlx_win :	ptr to the screen
**	dir :		orientation of the player
**	plane :		orientation of the camera plane
*/
typedef struct	s_game_engine
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_keypress	keys;
	t_map		map;
	double		move_speed;
	double		rot_speed;
	t_vect		dir;
	t_vect		plane;
	t_player	pl;
	int			screen_w;
	int			screen_h;
}				t_game_engine;

/*
**	Digital Differential Analysis algorithm
**	draw_start/end:	position on the screen of the column to be drawn
**	side_dist:	 	length of ray from current position to next x or y-side
**	delta:			length of ray from one x or y-side to next x or y-side
**	step:			what direction to step in x or y-direction (either +1 or -1)
**	camera_x:		pos on the camera plane. used to build ray_dir
**	map:			which box of the map we're in
*/
typedef struct	s_dda
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
	int			img_x;
	int			img_y;
	int			tex_x;
	int			tex_y;
}				t_dda;

int				init_engine(t_game_engine *ge);

/*
**	dda : raytracing engine
*/
void			init_dda(t_dda *dda, t_game_engine *ge);
void			detect_collision(t_dda *dda, t_game_engine *ge);
int				compute_dda(t_dda *dda, t_game_engine *ge);
t_cardinal		get_wall_orientation(t_dda *dda);

/*
**	Keyboards events
*/
void			move_front(t_game_engine *ge);
void			move_back(t_game_engine *ge);
void			move_left(t_game_engine *ge);
void			move_right(t_game_engine *ge);
void			rot_left(t_game_engine *ge);
void			rot_right(t_game_engine *ge);
int				key_hook(int keycode, void *param);
int				key_hook_press(int keycode, void *param);
int				key_hook_release(int keycode, void *param);
int				main_hook(void *param);
int				exit_hook(t_game_engine *ge);

/*
**	display
*/
int				img_vertline_put(t_dda *dda, t_game_engine *ge,
						t_img *tex, int tex_x, t_img *img);
int				draw(void *param);
int				compute_fps();
void			copy_pxl(char *dest, char *source, int bpp);
void			copy_ceil(int *img_y, t_game_engine *ge, int *img_n, t_img *img, t_dda *dda);
void			copy_floor(int *img_y, t_game_engine *ge, int *img_n, t_img *img);

/*
**	loading cub file
*/
int				load_cub_file(t_game_engine *ge, char *path);
int				load_map_dimensions(t_game_engine *ge, char *line);
int				load_colors(t_game_engine *ge, char *line);
int				load_sprite(t_game_engine *ge, char *line);
int				load_map(t_game_engine *ge, int fd, char *line);
int				load_textures(t_game_engine *ge, char *line);
int				load_line(t_game_engine *ge, char *line, int *n);
int				check_map(char *map);
t_cardinal		get_tex_orientation(char l);
void			*ft_realloc(void *p, size_t l, size_t newsize);

#endif
