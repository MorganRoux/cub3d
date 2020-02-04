/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:48:35 by mroux             #+#    #+#             */
/*   Updated: 2020/02/04 16:50:49 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	calc()
{
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	
}

int		key_hook(int keycode,void *param)
{
	(void)param;
	ft_printf("%d\n", keycode);
	return 1;
}

s_vect	intercept_x(GameEngine *ge)
{
	double	dx;
	double	dy;
	int 	step;
	s_vect	pos;
	int		hit;

	hit = 0;
	dy = ge->delta.y;
	if (ge->dir.x > 0)
	{
		dx = 1;
		pos.x = floor(ge->pl.pos.x);
		pos.y = ge->pl.pos.y + dy * (pos.x - ge->pl.pos.x);
		pos.x += dx;
		pos.y += dy;
		while (hit != 1 && pos.x > 0 && pos.y > 0 && pos.x + 1 < MAP_WIDTH && pos.y + 1 < MAP_HEIGHT )
		{
			hit = worldMap[(int)floor(pos.x)][(int)floor(pos.y)];
			pos.x += dx;
			pos.y += dy;
		}
	}

}
initGe(GameEngine *ge)
{
	ge->d_alpha = FOV / (SCREEN_WIDTH - 1);
	ge->dir.x = 1;
	ge->dir.y = 0;
	ge->pl.pos.x =22;
	ge->pl.pos.y = 12;
}
int		calc(void *mlx_ptr, void *mlx_win, GameEngine *ge)
{
	int n;
	initGe(ge);
	n = 0;

	while (n < SCREEN_WIDTH)
	{
		ge->alpha[n] = -FOV / 2 + n * ge->d_alpha;
		n++;
	}

	n = 0;
	while (n < SCREEN_WIDTH)
	{
		// d_x : y = GRID_SIZE
		ge->delta.x = tan(ge->alpha[n]) * GRID_SIZE;
		ge->delta.y = GRID_SIZE / tan(ge->alpha[n]);
		intercept_x(ge);
		intercept_y(ge);
		n++
	}
}

int		main(void)
{
	void		*mlx_ptr;
	void		*mlx_win;
	GameEngine	ge;

	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	if ((mlx_win = mlx_new_window(mlx_ptr, 100, 100, "Hello")) == NULL)
		return (0);
	// mlx_do_key_autorepeaton(mlx_ptr);
	// mlx_key_hook(mlx_win, &key_hook ,NULL);
	// mlx_loop(mlx_ptr);




	
}
