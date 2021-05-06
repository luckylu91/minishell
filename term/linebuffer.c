/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linebuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 10:30:32 by lzins             #+#    #+#             */
/*   Updated: 2021/05/06 11:45:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	linebuffer_add_insert(t_linebuffer *lb, int c)
{
	if (lb->i_max >= lb->size - 1)
	{
		lb->buffer = bigger_calloc(lb->buffer, lb->size, LINE_BUFFER_SIZE);
		lb->size += LINE_BUFFER_SIZE;
	}
	if (lb->i == lb->i_max)
		lb->buffer[lb->i_max] = (char)c;
	else
	{
		ft_memmove(lb->buffer + lb->i + 1, lb->buffer + lb->i, lb->i_max - lb->i);
		lb->buffer[lb->i] = (char)c;
	}
	lb->i_max++;
	lb->i++;
}

void	set_linebuffer_to(t_linebuffer *lb, char *str)
{
	int	n_buffer_chunks;
	int	str_len;

	if (lb->buffer)
		linebuffer_clear(lb);
	if (!str || !str[0])
		return ;
	str_len = ft_strlen(str);
	n_buffer_chunks = 1 + str_len / LINE_BUFFER_SIZE;
	lb->buffer = ft_calloc(n_buffer_chunks * LINE_BUFFER_SIZE, sizeof(char));
	ft_memcpy(lb->buffer, str, str_len);
	lb->size = n_buffer_chunks * LINE_BUFFER_SIZE;
	lb->i_max = str_len;
	lb->i = str_len;
}

void	linebuffer_delete(t_linebuffer *lb)
{
	if (lb->i > 0)
	{
		lb->i_max--;
		lb->i--;
		if (lb->i < lb->i_max)
			ft_memmove(lb->buffer + lb->i, lb->buffer + lb->i + 1, lb->i_max - lb->i);
		lb->buffer[lb->i_max] = '\0';
	}
}

void	linebuffer_clear(t_linebuffer *lb)
{
	wrap_free(lb->buffer);
	ft_bzero(lb, sizeof(t_linebuffer));
}
