/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hist_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:49:36 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 15:21:23 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

// rewind_hist and h->position state settings are there just in case
int	add_hist_line(t_hist *h, char *line)
{
	t_bilist	*last;
	char		*line_copy;

	rewind_hist(h);
	h->position_state = BOTTOM;
	line_copy = ft_strdup(line);
	if (!line_copy || !ft_bilstadd_front_content(&h->lines, line_copy))
	{
		free(line_copy);
		return (-1);
	}
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
