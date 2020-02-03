/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:38:10 by mroux             #+#    #+#             */
/*   Updated: 2019/11/04 13:38:32 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = NULL;
	if (*s == (char)c)
		ret = (char *)s;
	while (*s++ != 0)
	{
		if (*s == (char)c)
			ret = (char *)s;
	}
	return (ret);
}
