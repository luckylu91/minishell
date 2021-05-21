/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:06:20 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 16:30:45 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

/*
	if limit is reached or no lines in hist, returns 0 (some line to be shown)
	else returns 1
*/
void	move_hist(t_hist *h, int direction)
{
	if (!h->hlines)
		return ;
	if (direction > 0)
	{
		if (h->position_state == BOTTOM)
			h->position_state = MOVING;
		else
			h->hlines = ft_bilststep_blocking(h->hlines, 1);
	}
	if (direction < 0)
	{
		if (h->position_state == MOVING && !h->hlines->prev)
			h->position_state = BOTTOM;
		else
			h->hlines = ft_bilststep_blocking(h->hlines, -1);
	}
}
