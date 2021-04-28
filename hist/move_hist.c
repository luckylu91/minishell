/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:06:20 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 19:13:59 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

/*
	if limit is reached or no lines in hist, returns 0 (some line to be shown)
	else returns 1
*/
int	move_hist(t_hist *h, int direction)
{
	if (!h->lines)
		return (0);
	if (direction > 0)
	{
		if (!h->lines->next)
			return (0);
		ft_bilststep_blocking(h->lines, 1);
		return (1);
	}
	if (direction < 0)
	{
		if (!h->lines->prev)
			return (0);
		ft_bilststep_blocking(h->lines, -1);
		return (1);
	}
	return (0);
}
