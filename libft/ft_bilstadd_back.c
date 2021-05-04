/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:04:05 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 17:31:21 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bilstadd_back(t_bilist **alst, t_bilist *new)
{
	t_bilist *last;

	if (alst == NULL)
		return ;
	else if (*alst == NULL)
		*alst = new;
	else
	{
		last = ft_bilstlast(*alst);
		last->next = new;
		new->prev = last;
	}
}
