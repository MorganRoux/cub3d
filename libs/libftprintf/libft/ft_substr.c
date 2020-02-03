/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:20:08 by mroux             #+#    #+#             */
/*   Updated: 2019/11/05 10:50:50 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		lmax;
	size_t		n_copy;
	size_t		i;

	i = 0;
	lmax = ft_strlen(s);
	if (start >= lmax)
	{
		if (!(sub = (char *)malloc(1 * sizeof(char))))
			return (NULL);
		sub[0] = 0;
		return (sub);
	}
	if (start + len < lmax)
		n_copy = len;
	else
		n_copy = lmax - start;
	if (!(sub = (char *)malloc((n_copy + 1) * sizeof(char))))
		return (NULL);
	while (i < n_copy)
		sub[i++] = *(s++ + start);
	sub[i] = 0;
	return (sub);
}
