/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:34:44 by mroux             #+#    #+#             */
/*   Updated: 2019/11/04 18:05:56 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*ret;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	if (!(ret = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (i < len)
	{
		ret[i] = (*f)(i, s[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}
