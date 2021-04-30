/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:01:39 by lzins             #+#    #+#             */
/*   Updated: 2021/04/30 10:46:25 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bilist	*ft_bilstnew(void *content)
{
	t_bilist *new_elem;

	new_elem = wrap_malloc(sizeof(t_bilist));
	if (!new_elem)
		return (NULL);
	new_elem->content = content;
	new_elem->prev = NULL;
	new_elem->next = NULL;
	return (new_elem);
}
