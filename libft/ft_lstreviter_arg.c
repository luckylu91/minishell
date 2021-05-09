/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreviter_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:30:43 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 13:53:38 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstreviter_arg(t_list *lst, void *arg, t_fun2 f)
{
	if (!lst)
		return ;
	ft_lstreviter_arg(lst->next, arg, f);
	(*f)(lst->content, arg);
}
