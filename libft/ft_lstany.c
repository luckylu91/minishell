/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstany.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:31:57 by lzins             #+#    #+#             */
/*   Updated: 2021/03/24 15:35:29 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_lstany(t_list *lst, int (*booleval)(void *content))
{
	while (lst)
	{
		if ((*booleval)(lst->content))
			return (1);
		lst = lst->next;
	}
	return (0);
}