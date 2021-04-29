/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:06:20 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 15:03:38 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

/*
	if limit is reached or no lines in hist, returns 0 (some line to be shown)
	else returns 1
*/
void	move_hist(t_hist *h, int direction)
{
	if (!h->lines)
		return ;
	if (direction > 0)
	{
		if (h->position_state == BOTTOM)
			h->position_state = MOVING;
		else
			h->lines =  ft_bilststep_blocking(h->lines, 1);
	}
	if (direction < 0)
	{
		if (h->position_state == MOVING && !h->lines->prev)
			h->position_state = BOTTOM;
		else
			h->lines = ft_bilststep_blocking(h->lines, -1);
	}
}
