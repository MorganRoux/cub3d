/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:51:59 by mroux             #+#    #+#             */
/*   Updated: 2019/12/10 16:52:22 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ultoa_base(unsigned long n, char *base)
{
	size_t			len;
	unsigned long	nbr;
	char			*ret;
	long			nbase;

	if (base == 0)
		return (NULL);
	nbase = (long)ft_strlen(base);
	nbr = n;
	len = 1;
	while ((nbr = nbr / nbase) > 0)
		len++;
	if (!(ret = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	nbr = n;
	ret[len--] = 0;
	ret[len--] = base[nbr % nbase];
	while ((nbr = nbr / nbase) > 0)
		ret[len--] = base[nbr % nbase];
	return (ret);
}
