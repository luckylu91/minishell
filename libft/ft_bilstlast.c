/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:05:04 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 17:05:56 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bilist	*ft_bilstlast(t_bilist *blst)
{
	if (blst == NULL)
		return (NULL);
	while (blst->next != NULL)
		blst = blst->next;
	return (blst);
}
