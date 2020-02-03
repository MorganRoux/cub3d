/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_options_diux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:32:13 by mroux             #+#    #+#             */
/*   Updated: 2019/12/11 11:56:58 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		option_di(t_flags *flags, int n)
{
	int				len;
	char			*s;
	char			*zero;
	char			*nbr;

	nbr = ft_uitoa_base((n < 0) ? -n : n, "0123456789");
	len = flags->precision - (ft_strlen(nbr));
	len = len < 0 ? 0 : len;
	if (!(zero = ft_calloc(len + 1, sizeof(char))))
		return (-1);
	ft_memset(zero, '0', len);
	zero[len] = 0;
	s = ft_strjoin(zero, nbr);
	if (n < 0)
		s = ft_strjoin_ex("-", s, 2);
	s[0] = (n == 0 && flags->precision == 0) ? 0 : s[0];
	print_arg_nbr(s, flags);
	flags->nprint += (ft_strlen(s) > (unsigned long)flags->len) ? ft_strlen(s)
				: flags->len;
	free(nbr);
	free(s);
	free(zero);
	return (0);
}

int		option_ux(char *nbr, int n, t_flags *flags)
{
	int		len;
	char	*s;
	char	*zero;

	len = flags->precision - ft_strlen(nbr);
	len = len < 0 ? 0 : len;
	if (!(zero = ft_calloc(len + 1, sizeof(char))))
		return (-1);
	ft_memset(zero, '0', len);
	zero[len] = 0;
	s = ft_strjoin(zero, nbr);
	s[0] = (n == 0 && flags->precision == 0) ? 0 : s[0];
	print_arg_nbr(s, flags);
	flags->nprint += (ft_strlen(s) > (unsigned long)flags->len) ?
					ft_strlen(s) : flags->len;
	free(s);
	free(zero);
	return (0);
}

int		option_diux(va_list *ap, t_flags *flags, char type)
{
	char	*nbr;
	int		n;
	int		ret;

	n = va_arg(*ap, int);
	if (type == 'd' || type == 'i')
		return (option_di(flags, n));
	else if (type == 'x' || type == 'X')
		nbr = ft_uitoa_base(n, type == 'x' ? "0123456789abcdef"
										: "0123456789ABCDEF");
	else if (type == 'u')
		nbr = ft_uitoa_base(n, "0123456789");
	else
		return (0);
	ret = option_ux(nbr, n, flags);
	free(nbr);
	return (ret);
}
