/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:06:08 by mroux             #+#    #+#             */
/*   Updated: 2020/02/11 18:45:02 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		get_next_line(int fd, char **line)
{
	static t_fl		fl;
	int				ln;

	ln = 0;
	if (init(&fl, fd, line) == 0)
		return (-1);
	if (fl.pos == 0 &&
		(fl.bytes_read = read(fl.fd, fl.buffer, BUFFER_SIZE)) <= 0)
		return (fl.bytes_read);
	while ((ln = find_line(&fl)) == -1)
	{
		*line = ft_strnjoin(*line, fl.buffer + fl.pos, fl.bytes_read - fl.pos);
		fl.pos = 0;
		if ((fl.bytes_read = read(fl.fd, fl.buffer, BUFFER_SIZE)) <= 0)
		{
			reinit(&fl);
			return (fl.bytes_read);
		}
	}
	*line = ft_strnjoin(*line, fl.buffer + fl.pos, ln);
	fl.pos = (fl.pos + ln + 1 >= fl.bytes_read) ? 0 : fl.pos + ln + 1;
	return (1);
}
