/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:48:35 by mroux             #+#    #+#             */
/*   Updated: 2020/02/03 16:37:18 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libftprintf.h"

int		key_hook(int keycode,void *param)
{
	(void)param;
	ft_printf("%d\n", keycode);
	return 1;
}

int		main(void)
{
	void	*mlx_ptr;
	void	*mlx_win;

	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	if ((mlx_win = mlx_new_window(mlx_ptr, 100, 100, "Hello")) == NULL)
		return (0);
	mlx_key_hook(mlx_win, &key_hook ,NULL);
	mlx_loop(mlx_ptr);
}
