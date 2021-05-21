/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstany.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:31:57 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 14:34:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstany(t_list *lst, void *arg, t_bool_fun booleval)
{
	while (lst)
	{
		if ((*booleval)(lst->content, arg))
			return (1);
		lst = lst->next;
	}
	return (0);
}
