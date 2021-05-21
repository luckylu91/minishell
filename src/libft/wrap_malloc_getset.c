/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_malloc_getset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:07:10 by lzins             #+#    #+#             */
/*   Updated: 2021/05/19 17:31:14 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_get_malloc_list(void)
{
	static t_list	*malloc_list = NULL;

	return (&malloc_list);
}

t_before_exit_fun	ft_get_set_exit_fun(t_before_exit_fun fun)
{
	static t_before_exit_fun	exit_fun = NULL;

	if (fun)
	{
		exit_fun = fun;
		return (NULL);
	}
	return (exit_fun);
}

void	*ft_get_set_context(void *new_context)
{
	static void	*context = NULL;

	if (new_context)
	{
		context = new_context;
		return (NULL);
	}
	return (context);
}
