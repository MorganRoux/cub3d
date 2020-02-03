/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:17:46 by mroux             #+#    #+#             */
/*   Updated: 2019/12/03 10:25:13 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa_base(unsigned int n, char *base)
{
	size_t			len;
	unsigned int	nbr;
	char			*ret;
	int				nbase;

	if (base == 0)
		return (NULL);
	nbase = ft_strlen(base);
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
