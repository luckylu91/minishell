/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 23:18:14 by lzins             #+#    #+#             */
/*   Updated: 2021/04/30 23:31:56 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	lstremove_addr(t_list **alst, void *content)
{
	t_list *lst;
	t_list *prev;

	prev = NULL;
	lst = *alst;
	while (lst)
	{
		if (lst->content == content)
		{
			if (prev)
				prev->next = lst->next;
			else
				*alst = lst->next;
			ft_lstdelone(lst, free);
			return (1);
		}
		prev = lst;
		lst = lst->next;
	}
	return (0);
}

void	wrap_free(void *addr)
{
	t_list	**malloc_list;

	if (!addr)
		return ;
	malloc_list = ft_get_malloc_list();
	if (!lstremove_addr(malloc_list, addr))
	{
		ft_putendl_fd("Attempted wrap_free on an unknown value.",
				STDERR_FILENO);
		exit(-1);
	}
}
