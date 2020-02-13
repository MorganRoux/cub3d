/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:19:41 by mroux             #+#    #+#             */
/*   Updated: 2020/02/11 18:45:07 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_strnjoin(char *s1, char const *s2, size_t n)
{
	size_t	len1;
	size_t	len2;
	char	*ret;
	char	*str1;
	size_t	i;

	str1 = s1;
	i = 0;
	len1 = ft_strlen(s1);
	len2 = n;
	if (!(ret = (char *)malloc((len1 + len2 + 1) * sizeof(char))))
		return (NULL);
	while (i < len1)
		ret[i++] = *str1++;
	i = 0;
	while (i < len2)
		ret[len1 + i++] = *s2++;
	ret[len1 + len2] = 0;
	if (s1 != 0)
		free(s1);
	return (ret);
}

int		find_line(t_fl *fl)
{
	int	ln;

	ln = 0;
	if (fl->bytes_read == 0)
		return (-1);
	while (fl->buffer[fl->pos + ln] != '\n')
	{
		if (fl->pos + ln + 1 == fl->bytes_read)
			return (-1);
		ln++;
	}
	return (ln);
}

int		init(t_fl *fl, int fd, char **line)
{
	size_t	buff_size;

	if (BUFFER_SIZE == 0)
		return (0);
	buff_size = BUFFER_SIZE;
	fl->fd = fd;
	if (fl->buffer == 0)
	{
		if (!(fl->buffer = (char *)malloc(buff_size * sizeof(char))))
			return (0);
	}
	if (line == 0 || !(*line = (char *)malloc(1 * sizeof(char))))
		return (0);
	(*line)[0] = 0;
	return (1);
}

int		reinit(t_fl *fl)
{
	free(fl->buffer);
	fl->buffer = 0;
	fl->pos = 0;
	fl->bytes_read = 0;
	return (0);
}
