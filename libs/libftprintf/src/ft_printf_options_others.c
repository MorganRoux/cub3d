/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:30:11 by mroux             #+#    #+#             */
/*   Updated: 2019/12/11 11:57:02 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	option_c(va_list *ap, t_flags *flags)
{
	unsigned char	i;

	i = va_arg(*ap, int);
	print_arg_c(i, flags);
	flags->nprint += (1 > (unsigned long)flags->len) ?
					1 : flags->len;
}

void	option_pourcent(t_flags *flags)
{
	print_arg_c('%', flags);
	flags->nprint += (1 > (unsigned long)flags->len) ?
					1 : flags->len;
}

void	option_s(va_list *ap, t_flags *flags)
{
	char	*s;
	char	*tmp;

	if ((tmp = va_arg(*ap, char *)) == 0)
		tmp = ft_strdup("(null)");
	s = ft_substr(tmp, 0, flags->precision);
	flags->nprint += (ft_strlen(s) > (unsigned long)flags->len) ?
					ft_strlen(s) : flags->len;
	print_arg(s, flags);
	free(s);
	if (ft_strcmp("(null)", tmp) == 0)
		free(tmp);
}

void	option_p(va_list *ap, t_flags *flags)
{
	long	len;
	char	*s;
	char	*zero;
	char	*nbr;
	void	*p;

	p = va_arg(*ap, void *);
	nbr = ft_strjoin_ex("0x",
		ft_ultoa_base((unsigned long)p, "0123456789abcdef"), 2);
	len = flags->precision - ft_strlen(nbr);
	len = len < 0 ? 0 : len;
	if (!(zero = ft_calloc(len + 1, sizeof(char))))
		return ;
	ft_memset(zero, '0', len);
	zero[len] = 0;
	s = ft_strjoin(zero, nbr);
	print_arg(s, flags);
	flags->nprint += (ft_strlen(s) > (unsigned long)flags->len) ?
					ft_strlen(s) : flags->len;
	free(nbr);
	free(s);
	free(zero);
}
