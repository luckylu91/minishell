/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 18:27:08 by lzins             #+#    #+#             */
/*   Updated: 2021/05/05 10:56:19 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// //
// #define TEST_DEBUG_LEAKS
#include "libft.h"

t_list	**ft_get_malloc_list(void)
{
	static t_list *malloc_list = NULL;

	return (&malloc_list);
}

t_exit_fun	ft_get_set_exit_fun(t_exit_fun fun)
{
	static t_exit_fun exit_fun = NULL;

	if (fun)
	{
		exit_fun = fun;
		return (NULL);
	}
	return (exit_fun);
}

void	*ft_get_set_context(void *new_context)
{
	static void *context = NULL;

	if (new_context)
	{
		context = new_context;
		return (NULL);
	}
	return (context);
}

void	ft_malloc_list_clear(void)
{
	t_list **malloc_list;

	malloc_list = ft_get_malloc_list();
	ft_lstclear(malloc_list, free);
}

void	ft_exit(void)
{
	t_exit_fun	exit_fun;

	ft_malloc_list_clear();
	exit_fun = ft_get_set_exit_fun(NULL);
	if (exit_fun)
		exit_fun(ft_get_set_context(NULL));
}

static void	addback_malloc(void *new_malloc)
{
	t_list **malloc_list;
	t_list *new_elem;

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
	void *new_malloc;

	new_malloc = malloc(size);
	if (!new_malloc)
	{
		ft_exit();
		exit(-1);
	}
	addback_malloc(new_malloc);
	return (new_malloc);
}

