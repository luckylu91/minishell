/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:10:21 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 14:43:38 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bilstadd_front(t_bilist **alst, t_bilist *new)
{
	t_bilist	*first;

	if (alst == NULL)
		return ;
	first = ft_bilstfirst(*alst);
	new->next = first;
	if (first)
		first->prev = new;
	*alst = new;
}
