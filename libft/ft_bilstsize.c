/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:33:13 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 09:28:02 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_bilstsize(t_bilist *blst)
{
	int	i;

	blst = ft_bilstfirst(blst);
	i = 0;
	while (blst != NULL)
	{
		blst = blst->next;
		i++;
	}
	return (i);
}

