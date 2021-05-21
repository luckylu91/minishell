/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstfirst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:35:36 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 18:36:10 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bilist	*ft_bilstfirst(t_bilist *blst)
{
	if (blst == NULL)
		return (NULL);
	while (blst->prev != NULL)
		blst = blst->prev;
	return (blst);
}
