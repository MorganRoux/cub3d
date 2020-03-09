/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:57:42 by mroux             #+#    #+#             */
/*   Updated: 2020/03/09 16:27:29 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_dim_param(char **param)
{
	(void)param;
	int	i;

	i = 0;
	if (ft_strcmp(param[0], "R") != 0)
		return (ERROR_DIM);
	while(param[i] != 0)
		i++;
	if (i != 3)
		return (ERROR_DIM);
	return (OK);
}

int		check_color_param(char **param)
{
	(void)param;
	return (OK);
}

int		check_sprite_param(char **param)
{
	(void)param;
	return (OK);
}

int		check_tex_param(char **param)
{
	(void)param;
	return (OK);
}
