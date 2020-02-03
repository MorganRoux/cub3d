/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:56:39 by mroux             #+#    #+#             */
/*   Updated: 2019/12/11 12:00:07 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strjoin_ex(char *s1, char *s2, char select)
{
	char	*ret;
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = s1;
	str2 = s2;
	i = 0;
	if (!(ret = (char *)malloc((
		ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	while (i < ft_strlen(s1))
		ret[i++] = *str1++;
	i = 0;
	while (i < ft_strlen(s2))
		ret[ft_strlen(s1) + i++] = *str2++;
	ret[ft_strlen(s1) + ft_strlen(s2)] = 0;
	if ((select & 0b00000001) == 0b00000001)
		free(s1);
	if ((select & 0b00000010) == 0b00000010)
		free(s2);
	return (ret);
}
