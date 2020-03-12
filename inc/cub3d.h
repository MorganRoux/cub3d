/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:13:02 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 17:45:33 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/errno.h>
# include "libftprintf.h"
# include "get_next_line.h"
# include "keys.h"
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

enum				e_error_flags
{
	OK = 0,
	ERROR = 1,
	ERROR_DIM = 2,
	ERROR_COLORS = 4,
	ERROR_SPRITE = 8,
	ERROR_TEX = 16,
	ERROR_MAP = 32,
	ERROR_FLAGS = 64,
};

enum				e_init_flags
{
	FLAG_R = 1 << 0,
	FLAG_F = 1 << 1,
	FLAG_C = 1 << 2,
	FLAG_S = 1 << 3,
	FLAG_NO = 1 << 4,
	FLAG_SO = 1 << 5,
	FLAG_EA = 1 << 6,
	FLAG_WE = 1 << 7,
	FLAG_MAP = 1 << 8,
	FLAG_PLAYER = 1 << 9,
	FLAG_INIT_OK = 511,
};

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
typedef struct		s_vect
{
	double x;
	double y;
}					t_vect;

/*
**	int position only to use in sprite.c
*/
typedef struct		s_pxl
{
	int	x;
	int	y;
}					t_pxl;

typedef struct		s_pxl_color
{
	int r;
	int v;
	int	b;
}					t_color;

/*
**	Represent an img in mlx with extra properties
**	p_imp : 			pointer to the mlx image
**	data : 				ptr to the pixel data
**	size_line : 		the number of bytes used to store
**						one line of the image in memory
**	bits_per_pixels :	the depth of the image
**	path :				if provided, path on disk
*/
typedef	struct		s_img
{
	void	*p_img;
	char	*data;
	int		h;
	int		w;
	int		size_line;
	int		bits_per_pxl;
	int		endian;
	char	*path;
}					t_img;

typedef struct		s_sprite
{
	t_img	texture;
	t_vect	pos;
}					t_sprite;

/*
**	Map properties
**	p_map : 	ptr to the map
**	Textures : 	NO, SO, EA, WE
** 	colors : 	Floor, ceil
*/
typedef struct		s_world_map
{
	char		*p_map;
	size_t		size;
	int			w;
	int			h;
	t_img		textures[4];
	t_color		color[2];
	t_sprite	sprite_ref;
	t_sprite	*sprites;
	int			n_sprite;
	int			flags;
}					t_map;

typedef struct		s_player
{
	t_vect		pos;
}					t_player;

/*
**	Digital Differential Analysis algorithm
**	draw_start/end:	position on the screen of the column to be drawn
**	side_dist:	 	length of ray from current position to next x or y-side
**	delta:			length of ray from one x or y-side to next x or y-side
**	step:			what direction to step in x or y-direction (either +1 or -1)
**	camera_x:		pos on the camera plane. used to build ray_dir
**	map:			which box of the map we're seeking for a wall
*/
typedef struct		s_dda
{
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_x;
	int			draw_end_y;
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
	double		tex_y;
	double		*z_buffer;
	double		transform_x;
	double		transform_y;
	int			stripe_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			*sprite_order;
	double		*sprite_distance;
}					t_dda;

/*
**	Game Engine properties
**	mlx_ptr :	use by mlx
**	mlx_win :	ptr to the screen
**	dir :		orientation of the player
**	plane :		orientation of the camera plane
*/
typedef struct		s_game_engine
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
	t_dda		dda;
	int			screen_w;
	int			screen_h;
}					t_ge;

/*
**	Bitmap structures
*/
typedef struct		s_bitmap_file_header {
	unsigned char	bitmap_type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}					t_bfh;

typedef struct		s_bitmap_image_header {
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bih;

/*
** init
*/
int					init_engine(t_ge *ge);
int					init_dda(t_ge *ge);

/*
**	dda : raytracing engine
*/
void				update_dda(t_dda *dda, t_ge *ge);
void				detect_collision(t_dda *dda, t_ge *ge);
int					compute_dda(t_dda *dda, t_ge *ge);
t_cardinal			get_wall_orientation(t_dda *dda);

/*
**	Keyboards events
*/
void				move_front(t_ge *ge);
void				move_back(t_ge *ge);
void				move_left(t_ge *ge);
void				move_right(t_ge *ge);
void				rot_left(t_ge *ge);
void				rot_right(t_ge *ge);
int					key_hook(int keycode, void *param);
int					key_hook_press(int keycode, void *param);
int					key_hook_release(int keycode, void *param);
int					main_hook(void *param);
int					exit_hook(t_ge *ge);

/*
**	display
*/
int					img_vertline_put(t_dda *dda, t_ge *ge,
						t_img *tex, t_img *img);
int					draw_world(t_ge *ge, t_img *img);
int					draw_sprite(t_ge *ge, t_img *img);
int					draw(void *param);
int					compute_fps();
void				copy_pxl(char *dest, char *source, int bpp);
void				copy_ceil(t_ge *ge, int *img_n,
							t_img *img, t_dda *dda);
void				copy_floor(t_ge *ge, int *img_n,
							t_img *img, t_dda *dda);
int					img_to_bmp(t_img *img, char *file_name);

void				transform_sprite(t_ge *ge, t_sprite *sprite);
void				sort_sprite(t_ge *ge, int *sprite_order,
								double *sprite_distance);
/*
**	loading cub file
*/
int					load_cub_file(t_ge *ge, char *path);
int					load_map_dimensions(t_ge *ge, char *line);
int					load_colors(t_ge *ge, char *line);
int					load_sprite(t_ge *ge, char *line);
int					load_map(t_ge *ge, int fd, char *firstline);
int					load_textures(t_ge *ge, char *line);
int					make_rect(int w, char **lines);
int					flood_map(t_map *map, char **lines);
int					check_map(t_ge *ge);
int					check_dim_param(char **param);
int					check_color_param(char **param);
int					check_sprite_param(char **param);
int					check_tex_param(char **param);

/*
**	utils
*/
int					check_number(char *s);
int					load_line(t_ge *ge, char *line, int *n);
t_cardinal			get_tex_orientation(char l);
void				*ft_realloc(void *p, size_t l, size_t newsize);
void				replace_comma(char *line);
int					check_map_line(char *line);
void				free_lines(char **lines);
char				**create_new_line(char **lines, char *newline, int n_lines);
int					init_sprite_ref(t_sprite *sprite_ref, t_ge *ge);
void				flag_textures(t_ge *ge, char *line);
void				print_map(char **lines);

#endif
