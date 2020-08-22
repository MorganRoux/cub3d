/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 20:37:57 by myoung            #+#    #+#             */
/*   Updated: 2020/02/19 16:06:43 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/*
** char *string = ""
**	"asdfhgzxcv"		This string has the matching symbol or letter
**	"bqweryt123"		for the index of the keycode for the key.
**	"465=97-80]"		if you press KEY_BRACE_R or ]
**	"ou[ip lj\"k"		You could use string[30] or string[KEY_BRACE_R]
**	";\\,/nm.  ` "		to access the matching symbol or letter.
**	"	. * +   "
**	"/ -  =012345"		If you find anything missing please let me know.
**	"67 89";
*/

# define X11_KEY_PRESS          2
# define X11_KEY_PRESS_M        1
# define X11_KEY_RELEASE        3
# define X11_KEY_RELEASE_M      2

# define KEY_ESCAPE 65307
# define KEY_S 115
# define KEY_D 100
# define KEY_W 122
# define KEY_A 113
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

typedef struct	s_keys
{
	int			a:1;
	int			s:1;
	int			d:1;
	int			f:1;
	int			h:1;
	int			g:1;
	int			z:1;
	int			x:1;
	int			c:1;
	int			v:1;
	int			b:1;
	int			q:1;
	int			w:1;
	int			e:1;
	int			r:1;
	int			y:1;
	int			t:1;
	int			one:1;
	int			two:1;
	int			three:1;
	int			four:1;
	int			six:1;
	int			five:1;
	int			nine:1;
	int			seven:1;
	int			eight:1;
	int			zero:1;
	int			brace_r:1;
	int			o:1;
	int			u:1;
	int			brace_l:1;
	int			i:1;
	int			p:1;
	int			l:1;
	int			j:1;
	int			k:1;
	int			semi:1;
	int			n:1;
	int			m:1;
	int			tab:1;
	int			plus:1;
	int			minus:1;
	int			left:1;
	int			right:1;
	int			down:1;
	int			up:1;
}				t_keys;
#endif
