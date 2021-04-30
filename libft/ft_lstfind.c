/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:09:21 by lzins             #+#    #+#             */
/*   Updated: 2021/04/30 23:23:20 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *content, size_t content_size)
{
	while (lst)
	{
		if (!ft_memcmp(lst->content, content, content_size))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
