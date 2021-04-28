/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hist_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:49:36 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 19:23:32 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

int	add_hist_line(t_hist *h, char *line)
{
	t_bilist *last;
	if (!ft_bilstadd_front_content(&h->lines, line))
		return (-1);
	if (h->len == h->hist_size)
	{
		last = ft_bilstlast(h->lines);
		if (last->prev)
			last->prev->next = NULL;
		ft_bilstdelone(last, free);
	}
	else
		h->len++;
	return (1);
}
