/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilststep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:13:08 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 17:20:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bilist	*next_one(t_bilist *blst, int *n_steps)
{
	if (!blst)
		return (NULL);
	if (*n_steps > 0)
	{
		(*n_steps)--;
		return (blst->next);
	}
	if (*n_steps < 0)
	{
		(*n_steps)++;
		return (blst->prev);
	}
	return (blst);
}

t_bilist	*ft_bilststep(t_bilist *blst, int n_steps)
{
	while (blst)
	{
		if (n_steps == 0)
			return (blst);
		blst = next_one(blst, &n_steps);
	}
	return (NULL);
}
