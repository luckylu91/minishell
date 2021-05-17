/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 23:18:14 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:11:13 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static int	lstremove_addr(t_list **alst, void *content)
{
	t_list	*lst;
	t_list	*prev;

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
			free(lst->content);
			free(lst);
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
		printf("Attempted wrap_free on an unknown value : %p\n", addr);
		exit(-1);
	}
}
