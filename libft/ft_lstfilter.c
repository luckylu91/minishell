/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfilter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 13:41:47 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 14:40:43 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*lstfilter_rec(t_list *lst, void *arg, t_bool_fun to_keep, t_del_fun del)
{
	t_list	*res;

	if (!lst)
		return (NULL);
	res = lstfilter_rec(lst->next, arg, to_keep, del);
	if (!to_keep(lst->content, arg))
		ft_lstdelone(lst, del);
	else
	{
		lst->next = res;
		res = lst;
	}
	return (res);
}

void	ft_lstfilter(t_list **alst, void *arg, t_bool_fun to_keep, t_del_fun del)
{
	*alst = lstfilter_rec(*alst, arg, to_keep, del);
}
