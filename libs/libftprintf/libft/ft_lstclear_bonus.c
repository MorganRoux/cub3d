/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:26:39 by mroux             #+#    #+#             */
/*   Updated: 2019/11/07 10:00:16 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*prev;

	if (lst == NULL || *lst == NULL)
		return ;
	list = *lst;
	while (list != 0)
	{
		prev = list;
		list = list->next;
		if (prev->content != NULL && del != NULL)
			(*del)(prev->content);
		free(prev);
		prev = 0;
	}
	*lst = 0;
}
