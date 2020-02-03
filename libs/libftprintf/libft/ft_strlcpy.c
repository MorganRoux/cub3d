/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:31:49 by mroux             #+#    #+#             */
/*   Updated: 2019/11/04 13:31:51 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen)
{
	const size_t srclen = ft_strlen(src);

	if (srclen + 1 < maxlen)
	{
		memcpy(dst, src, srclen + 1);
	}
	else if (maxlen != 0)
	{
		memcpy(dst, src, maxlen - 1);
		dst[maxlen - 1] = '\0';
	}
	return (srclen);
}
