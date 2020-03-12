/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:53:43 by mroux             #+#    #+#             */
/*   Updated: 2020/03/12 10:34:23 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
int		is_charset(char c, char *charset)
{
	while (*charset != 0)
	{
		if (c == *charset++)
			return (1);
	}
	return (0);
}

int		compute_n_words(char *s, char *charset)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i] != 0)
	{
		if (!(is_charset(s[i], charset)))
		{
			while (!(is_charset(s[i], charset)) && s[i] != 0)
				i++;
			n++;
		}
		if (s[i] != 0)
			i++;
	}
	return (n);
}

char	**alloc_memory(char *s, char *charset, int n_words)
{
	char	**ret;
	int		n;
	int		i;

	n = 0;
	if (!(ret = (char **)malloc(sizeof(char **) * (n_words + 1))))
		return (0);
	while (*s != 0)
	{
		i = 0;
		if (!(is_charset(*s, charset)))
		{
			while (!(is_charset(*s, charset)) && *s++ != 0)
				i++;
			if (!(ret[n] = (char *)malloc(sizeof(char *) * (i + 1))))
				return (0);
			n++;
		}
		if (*s != 0)
			s++;
	}
	ret[n_words] = 0;
	return (ret);
}

void	fill(char *s, char *charset, char **ret)
{
	int i;
	int n;

	n = 0;
	while (*s != 0)
	{
		i = 0;
		if (!(is_charset(*s, charset)))
		{
			while (!(is_charset(*s, charset)) && *s != 0)
				*(ret[n] + i++) = *s++;
			*(ret[n] + i) = 0;
			n++;
		}
		if (*s != 0)
			s++;
	}
}

char	**ft_split_ex(char *str, char *charset)
{
	char	**ret;
	int		n_words;

	ret = 0;
	n_words = compute_n_words(str, charset);
	ret = alloc_memory(str, charset, n_words);
	if (ret != 0)
		fill(str, charset, ret);
	return (ret);
}
