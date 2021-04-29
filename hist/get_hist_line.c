/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hist_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:15:30 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 15:03:17 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

char	*get_hist_line(t_hist *h)
{
	if (!h->lines || h->position_state == BOTTOM)
		return (NULL);
	return (h->lines->content);
}
