/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:36:19 by mroux             #+#    #+#             */
/*   Updated: 2019/11/04 12:36:25 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*ptr;
	size_t	i;

	i = 0;
	total = size * count;
	if (!(ptr = (char *)malloc(total)))
		return (NULL);
	while (i < total)
		ptr[i++] = 0;
	return (ptr);
}
