/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hist_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:15:30 by lzins             #+#    #+#             */
/*   Updated: 2021/05/01 10:58:06 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

char	*get_hist_line(t_hist *h)
{
	if (!h->hlines || h->position_state == BOTTOM)
		return (NULL);
	return (h->hlines->content);
}
