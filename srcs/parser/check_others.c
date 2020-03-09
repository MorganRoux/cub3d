/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:57:42 by mroux             #+#    #+#             */
/*   Updated: 2020/03/09 18:11:24 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_dim_param(char **param)
{
	int	i;

	i = 1;
	if (ft_strcmp(param[0], "R") != 0)
		return (ERROR_DIM);
	while(param[i] != 0)
	{
		if (check_number(param[i]) == ERROR)
			return (ERROR_DIM); 
		i++;
	}
	if (i != 3)
		return (ERROR_DIM);
	return (OK);
}

int		check_color_param(char **param)
{
	int	i;

	i = 1;
	if (ft_strcmp(param[0], "F") != 0 && ft_strcmp(param[0], "C") != 0)
		return (ERROR_COLORS);
	while(param[i] != 0)
	{
		if (check_number(param[i]) == ERROR)
			return (ERROR_COLORS); 
		i++;
	}
	if (i != 4)
		return (ERROR_COLORS);
	return (OK);
}

int		check_sprite_param(char **param)
{
	int	i;
	int	fl;
	
	i = 0;
	if (ft_strcmp(param[0], "S") != 0)
		return (ERROR_SPRITE);
	while(param[i] != 0) 
		i++;
	if (i != 2 || (fl = open(param[1], O_RDONLY)) < 0)
		return (ERROR_SPRITE);
	close(fl);
	return (OK);
}

int		check_tex_param(char **param)
{
	int	i;
	int	fl;
	
	i = 0;
	if (ft_strcmp(param[0], "NO") != 0 &&
		ft_strcmp(param[0], "SO") != 0 &&
		ft_strcmp(param[0], "EA") != 0 &&
		ft_strcmp(param[0], "WE") != 0)
		return (ERROR_TEX);
	while(param[i] != 0) 
		i++;
	if (i != 2 || (fl = open(param[1], O_RDONLY)) < 0)
		return (ERROR_TEX);
	close(fl);
	return (OK);
}
