/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:40:24 by lzins             #+#    #+#             */
/*   Updated: 2021/05/05 19:03:10 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_current_line(t_linebuffer *lb, t_hist *h, int fd_out)
{
	char *histline;

	histline = get_hist_line(h);
	if (histline)
		ft_putstr_fd(histline, fd_out);
	if (lb->buffer)
		ft_putstr_fd(lb->buffer, fd_out);
}
