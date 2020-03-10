/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:25:19 by mroux             #+#    #+#             */
/*   Updated: 2020/03/10 18:03:28 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int		make_rect(int w, char **lines)
{
	int		i;
	int		l;

	i = 0;
	while (lines[i] != 0)
	{
		l = ft_strlen(lines[i]);
		printf("%d-%d ! ", l, w);
		getchar();
		if ((lines[i] = (char *)ft_realloc(lines[i], l, w + 1)) == NULL)
			return (ERROR);
		while (l < w)
			lines[i][l++] = '3';
		i++;
	}
	return (OK);
}

char	**flood_map(int w, int h, char **lines)
{
	char 	**s;
	(void)h;
	s = lines;
	printf("\n");
	while(*lines != 0)
		printf("%s\n", *lines++);
	getchar();
	lines = s;
	if (make_rect(w, lines) == ERROR)
		return (NULL);
	//lines = s;
	printf("\n");
	while(*lines != 0)
		printf("%s\n", *lines++);
	getchar();
	lines = s;
	return (lines);
}