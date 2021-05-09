/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:14:01 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 14:34:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_dup_fun dup, t_del_fun del)
{
	t_list	*new;
	t_list	*new_mov;
	t_list	*new_elem;

	(void)del;
	if (lst == NULL)
		return (NULL);
	new = ft_lstnew((*dup)(lst->content));
	new_mov = new;
	while ((lst = lst->next) != NULL)
	{
		new_elem = ft_lstnew((*dup)(lst->content));
		new_mov->next = new_elem;
		new_mov = new_mov->next;
	}
	return (new);
}
