/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_hist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:39:42 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 14:13:56 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

void	destroy_hist(t_hist *h)
{
	free(h->histfile_name);
	ft_bilstclear(&h->file_lines, free);
	ft_bilstclear(&h->lines, free);
	free(h);
}
