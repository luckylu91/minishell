/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linebuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 10:30:32 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 13:31:09 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

extern t_minishell g_global_var;

void	linebuffer_add_insert(int c)
{
	t_linebuffer	*lb;

	lb = g_global_var.lb;
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

void	set_linebuffer_to(char *str)
{
	int				n_buffer_chunks;
	int				str_len;
	t_linebuffer	*lb;

	lb = g_global_var.lb;
	if (lb->buffer)
		linebuffer_clear();
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

void	linebuffer_clear(void)
{
	t_linebuffer	*lb;

	lb = g_global_var.lb;
	wrap_free(lb->buffer);
	ft_bzero(lb, sizeof(t_linebuffer));
}

void	linebuffer_delete_one(void)
{
	t_linebuffer	*lb;
	char			**tc;

	lb = g_global_var.lb;
	tc = g_global_var.termcaps;
	if (lb->i > 0)
	{
		tputs(tc[MOVE_LEFT_ONE], 1, ft_putchar);
		tputs(tc[DELETE_CHAR], 1, ft_putchar);
		lb->i_max--;
		lb->i--;
		if (lb->i < lb->i_max)
			ft_memmove(lb->buffer + lb->i, lb->buffer + lb->i + 1, lb->i_max - lb->i);
		lb->buffer[lb->i_max] = '\0';
	}
}
