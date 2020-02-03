/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:39:07 by mroux             #+#    #+#             */
/*   Updated: 2019/11/04 13:40:09 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int i;
	unsigned int j;
	unsigned int size;

	i = -1;
	j = 0;
	size = 0;
	while (needle[size] != '\0')
		size++;
	if (size == 0)
		return ((char *)haystack);
	while (haystack[++i] != 0)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] == needle[j] && (i + j) < len)
			{
				if (j == size - 1)
					return ((char *)&haystack[i]);
				j++;
			}
		}
	}
	return (NULL);
}
