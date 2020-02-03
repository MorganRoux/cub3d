/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prints.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:28:56 by mroux             #+#    #+#             */
/*   Updated: 2019/12/10 19:10:36 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_arg(char *s, t_flags *flags)
{
	char	c;
	int		i;
	int		l;

	if (flags->left_pad)
	{
		i = 0;
		while (s[i] != 0)
			ft_putchar_fd(s[i++], 1);
		while (i++ < flags->len)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		c = (flags->zero_pad && flags->precision == -1) ? '0' : ' ';
		l = flags->len - ft_strlen(s);
		i = 0;
		while (i++ < l)
			ft_putchar_fd(c, 1);
		ft_putstr_fd(s, 1);
	}
}

void	print_arg_nbr_right(char *s, t_flags *flags)
{
	char	c;
	int		i;

	i = 0;
	if (flags->zero_pad && flags->precision == -1)
	{
		c = '0';
		if (s != 0 && s[0] == '-')
		{
			ft_putchar_fd('-', 1);
			s++;
			i++;
		}
	}
	else
		c = ' ';
	while (i++ < flags->len - (int)ft_strlen(s))
		ft_putchar_fd(c, 1);
	ft_putstr_fd(s, 1);
}

void	print_arg_nbr(char *s, t_flags *flags)
{
	int		i;

	i = 0;
	if (flags->left_pad)
	{
		while (s[i] != 0)
			ft_putchar_fd(s[i++], 1);
		while (i++ < flags->len)
			ft_putchar_fd(' ', 1);
	}
	else
		print_arg_nbr_right(s, flags);
}

void	print_arg_c(char c, t_flags *flags)
{
	char	fill;
	int		i;
	int		l;

	if (flags->left_pad)
	{
		i = 1;
		ft_putchar_fd(c, 1);
		while (i++ < flags->len)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		fill = (flags->zero_pad && flags->precision == -1) ? '0' : ' ';
		l = flags->len - 1;
		i = 0;
		while (i++ < l)
			ft_putchar_fd(fill, 1);
		ft_putchar_fd(c, 1);
	}
}
