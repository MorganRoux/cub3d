/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:19:41 by mroux             #+#    #+#             */
/*   Updated: 2019/11/09 12:16:29 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ret;
	size_t	i;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ret = (char *)malloc((len1 + len2 + 1) * sizeof(char))))
		return (NULL);
	while (i < len1)
		ret[i++] = *s1++;
	i = 0;
	while (i < len2)
		ret[len1 + i++] = *s2++;
	ret[len1 + len2] = 0;
	return (ret);
}
