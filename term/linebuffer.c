/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linebuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 10:30:32 by lzins             #+#    #+#             */
/*   Updated: 2021/05/01 10:45:51 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	linebuffer_add(t_linebuffer *lb, int c)
{
	if (lb->i == lb->size)
		lb->buffer = bigger_calloc(lb->buffer, lb->size, LINE_BUFFER_SIZE);
	// if (!line)
	// 	exit_properly(-1, h);
	lb->buffer[lb->i] = (char)c;
	lb->i++;
}

void	linebuffer_delete(t_linebuffer *lb)
{
	if (lb->i > 0)
		lb->buffer[--lb->i] = '\0';
}

void	linebuffer_clear(t_linebuffer *lb)
{
	wrap_free(lb->buffer);
	lb->buffer = NULL;
	lb->i = 0;
	lb->size = 0;
}
