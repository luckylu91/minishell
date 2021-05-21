/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_hist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:39:42 by lzins             #+#    #+#             */
/*   Updated: 2021/05/08 15:24:08 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

void	destroy_hist(t_hist **h)
{
	wrap_free((*h)->histfile_name);
	ft_bilstclear(&(*h)->file_lines, wrap_free);
	ft_bilstclear(&(*h)->hlines, wrap_free);
	wrap_free(*h);
	*h = 0;
}
