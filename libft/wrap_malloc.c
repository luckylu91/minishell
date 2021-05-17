/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 18:27:08 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:08:19 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #define TEST_DEBUG_LEAKS
#include "libft.h"

static void	ft_lstclear_nowrap(t_list **lst)
{
	t_list	*lst_mov1;
	t_list	*lst_mov2;

	if (lst == NULL)
		return ;
	lst_mov1 = *lst;
	while (lst_mov1 != NULL)
	{
		lst_mov2 = lst_mov1->next;
		free(lst_mov1->content);
		free(lst_mov1);
		lst_mov1 = lst_mov2;
	}
	*lst = NULL;
}

void	ft_malloc_list_clear(void)
{
	t_list	**malloc_list;

	malloc_list = ft_get_malloc_list();
	ft_lstclear_nowrap(malloc_list);
}

void	ft_exit(void)
{
	t_before_exit_fun	before_exit_fun;
	int					ret;

	before_exit_fun = ft_get_set_exit_fun(NULL);
	if (before_exit_fun)
		ret = before_exit_fun(ft_get_set_context(NULL));
	else
		ret = 0;
	ft_malloc_list_clear();
	exit(ret);
}

static void	addback_malloc(void *new_malloc)
{
	t_list	**malloc_list;
	t_list	*new_elem;

	malloc_list = ft_get_malloc_list();
	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
	{
		ft_exit();
		exit(-1);
	}
	new_elem->content = new_malloc;
	new_elem->next = NULL;
	ft_lstadd_back(malloc_list, new_elem);
}

void	*wrap_malloc(size_t size)
{
	void	*new_malloc;

	new_malloc = malloc(size);
	if (!new_malloc)
	{
		ft_exit();
		exit(-1);
	}
	addback_malloc(new_malloc);
	return (new_malloc);
}
