/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:58:16 by mroux             #+#    #+#             */
/*   Updated: 2019/12/11 11:02:12 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *flags)
{
	flags->left_pad = 0;
	flags->zero_pad = 0;
	flags->len = 0;
	flags->precision = -1;
}

int		ft_printf(const char *s, ...)
{
	int		ret;
	va_list	ap;
	t_flags	flags;

	flags.nprint = 0;
	va_start(ap, s);
	ret = 0;
	if (s == 0)
		return (-1);
	while (*s != 0)
	{
		init_flags(&flags);
		if ((ret = handle_args(&ap, &s, &flags)) == 0)
		{
			ft_putchar_fd(*s++, 1);
			flags.nprint++;
		}
		if (ret == -1)
			return (-1);
	}
	return (flags.nprint);
}
