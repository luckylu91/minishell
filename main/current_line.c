/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:40:24 by lzins             #+#    #+#             */
/*   Updated: 2021/05/08 16:59:38 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_current_line(void)
{
	char *histline;
	t_linebuffer *lb;
	t_hist *h;
	int fd_out;

	lb = g_global_var.lb;
	h = g_global_var.h;
	fd_out = g_global_var.fd_out;
	histline = get_hist_line(h);
	if (histline)
		ft_putstr_fd(histline, fd_out);
	if (lb->buffer)
		ft_putstr_fd(lb->buffer, fd_out);
}
