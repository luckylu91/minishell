/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:34:13 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 16:00:59 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front_content(t_list **alst, void *content)
{
	t_list *new_elem;

	if (!alst)
		return ;
	new_elem = ft_lstnew(content);
	ft_lstadd_front(alst, new_elem);
}