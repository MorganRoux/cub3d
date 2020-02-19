/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_fps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:17:51 by mroux             #+#    #+#             */
/*   Updated: 2020/02/19 16:20:45 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		compute_fps(void)
{
	static clock_t	start = 0;
	static clock_t	end = 0;
	double			cpu_time_used;
	int				fps;

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	fps = 1.0 / cpu_time_used;
	start = end;
	return (fps);
}
