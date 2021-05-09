/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreviter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:30:43 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 14:32:11 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstreviter(t_list *lst, void *arg, t_fun f)
{
	if (!lst)
		return ;
	ft_lstreviter(lst->next, arg, f);
	(*f)(lst->content, arg);
}
