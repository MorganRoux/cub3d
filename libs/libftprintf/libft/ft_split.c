/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:28:29 by mroux             #+#    #+#             */
/*   Updated: 2019/11/05 14:48:06 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static	size_t	count_words(char const *s, char c)
{
	size_t	n;

	n = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s != 0)
		{
			n++;
			while (*s != c && *s != 0)
				s++;
		}
	}
	return (n);
}

static	char	**alloc_mem(int n_words, char const *s, char c)
{
	char	**strs;
	char	**ret;
	int		len;

	len = 0;
	if (!(strs = (char **)malloc((n_words + 1) * sizeof(char *))))
		return (NULL);
	ret = strs;
	strs[n_words] = 0;
	while (n_words-- > 0)
	{
		len = 0;
		while (*s == c)
			s++;
		while (s[len] != c && s[len] != 0)
			len++;
		s += len;
		if (!(*strs = (char *)malloc((len + 1) * sizeof(char))))
			return (NULL);
		strs++;
	}
	return (ret);
}

char			**ft_split(char const *s, char c)
{
	size_t	n_words;
	size_t	i;
	char	**ret;
	char	**strs;

	n_words = count_words(s, c);
	strs = alloc_mem(n_words, s, c);
	ret = strs;
	while (n_words-- > 0)
	{
		i = 0;
		while (*s == c)
			s++;
		while (*s != c && *s != 0)
			(*strs)[i++] = *s++;
		(*strs++)[i] = 0;
	}
	return (ret);
}
