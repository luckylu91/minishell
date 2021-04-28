/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:10:21 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 17:12:06 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bilstadd_front(t_bilist **alst, t_bilist *new)
{
	if (alst == NULL)
		return ;
	new->next = *alst;
	if (*alst)
		(*alst)->prev = new;
	*alst = new;
}
