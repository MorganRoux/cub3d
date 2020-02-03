/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:58:33 by mroux             #+#    #+#             */
/*   Updated: 2019/12/11 11:50:49 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libftprintf.h"
# include <stdarg.h>
# define RIGHT_ADJUSTED 0
# define LEFT_ADJUSTED 1
# define ZERO_PADDING 2
# define PRECISION 3

typedef struct	s_flags
{
	int		len;
	int		left_pad;
	int		zero_pad;
	char	c;
	int		precision;
	int		nprint;
}				t_flags;

void			print_arg(char *s, t_flags *flags);
void			print_arg_nbr_right(char *s, t_flags *flags);
void			print_arg_nbr(char *s, t_flags *flags);
void			print_arg_c(char c, t_flags *flags);
int				option_di(t_flags *flags, int n);
int				option_ux(char *nbr, int n, t_flags *flags);
int				option_diux(va_list *ap, t_flags *flags, char type);
void			option_c(va_list *ap, t_flags *flags);
void			option_pourcent(t_flags *flags);
void			option_s(va_list *ap, t_flags *flags);
void			option_p(va_list *ap, t_flags *flags);
int				ft_printf(const char *s, ...);
int				handle_args(va_list *ap, const char **s, t_flags *flags);
char			is_flag(char c);
char			*ft_strjoin_ex(char *s1, char *s2, char select);

#endif
