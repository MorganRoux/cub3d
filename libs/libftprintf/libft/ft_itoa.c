/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:02:56 by mroux             #+#    #+#             */
/*   Updated: 2019/11/04 18:02:30 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*base;
	size_t			len;
	unsigned int	nbr;
	char			*ret;

	base = ft_strdup("0123456789");
	nbr = (unsigned int)(n < 0) ? -n : n;
	len = (n < 0) ? 2 : 1;
	while ((nbr = nbr / 10) > 0)
		len++;
	if (!(ret = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	nbr = (unsigned int)(n < 0) ? -n : n;
	ret[len--] = 0;
	ret[len--] = base[nbr % 10];
	while ((nbr = nbr / 10) > 0)
		ret[len--] = base[nbr % 10];
	if (n < 0)
		ret[0] = '-';
	return (ret);
}
