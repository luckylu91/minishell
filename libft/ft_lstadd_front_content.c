/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:34:13 by lzins             #+#    #+#             */
/*   Updated: 2021/04/27 18:35:17 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_front_content(t_list **alst, void *content)
{
	t_list *new_elem;

	if (!alst)
		return (0);
	new_elem = ft_lstnew(content);
	if (!new_elem)
		return (0);
	ft_lstadd_front(alst, new_elem);
	return (1);
}