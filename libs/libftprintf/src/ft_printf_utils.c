/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:10:46 by mroux             #+#    #+#             */
/*   Updated: 2019/12/11 11:56:57 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_flags(const char **s, t_flags *flags)
{
	while (**s == '-' || **s == '0')
	{
		if (**s == '-')
			flags->left_pad = 1;
		else if (**s == '0')
			flags->zero_pad = 1;
		(*s)++;
	}
}

void	handle_digits(va_list *ap, const char **s, t_flags *flags)
{
	if (ft_isdigit(**s))
	{
		flags->len = ft_atoi(*s);
		while (ft_isdigit(**s))
			(*s)++;
	}
	else if (**s == '*')
	{
		flags->len = va_arg(*ap, int);
		(*s)++;
	}
	if (flags->len < 0)
	{
		flags->len = -flags->len;
		flags->left_pad = 1;
	}
}

void	handle_precision(va_list *ap, const char **s, t_flags *flags)
{
	if (**s == '.')
	{
		flags->precision = 0;
		(*s)++;
		if (ft_isdigit(**s))
		{
			flags->precision = ft_atoi(*s);
			while (ft_isdigit(**s))
				(*s)++;
		}
		else if (**s == '*')
		{
			flags->precision = va_arg(*ap, int);
			flags->precision = (flags->precision < 0) ? -1 : flags->precision;
			(*s)++;
		}
	}
}

int		handle_type(va_list *ap, const char **s, t_flags *flags)
{
	if (**s == 'd' || **s == 'i' || **s == 'u' || **s == 'x' || **s == 'X')
	{
		if (option_diux(ap, flags, **s) == -1)
			return (-1);
	}
	else if (**s == 'c')
		option_c(ap, flags);
	else if (**s == 's')
		option_s(ap, flags);
	else if (**s == 'p')
		option_p(ap, flags);
	else if (**s == '%')
		option_pourcent(flags);
	return (0);
}

int		handle_args(va_list *ap, const char **s, t_flags *flags)
{
	if (**s == '%')
	{
		(*s)++;
		if (**s == '%')
		{
			ft_putchar_fd(*(*s)++, 1);
			flags->nprint++;
		}
		else
		{
			handle_flags(s, flags);
			handle_digits(ap, s, flags);
			handle_precision(ap, s, flags);
			if (handle_type(ap, s, flags) == -1)
				return (-1);
			(*s)++;
		}
		return (1);
	}
	return (0);
}
