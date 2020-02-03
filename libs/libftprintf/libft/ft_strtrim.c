/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:40:28 by mroux             #+#    #+#             */
/*   Updated: 2019/11/05 11:08:31 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		find(char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*ret;

	i = 0;
	while (find(s1[i], set) == 1)
		i++;
	start = i;
	if (s1[i] == 0)
		len = 0;
	else
	{
		while (s1[i] != 0)
			i++;
		i--;
		while (find(s1[i], set) == 1)
			i--;
		len = i - start + 1;
	}
	ret = ft_substr(s1, start, len);
	return (ret);
}
