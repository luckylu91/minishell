/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linebuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 10:30:32 by lzins             #+#    #+#             */
/*   Updated: 2021/05/26 19:12:12 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	linebuffer_add_insert(int c, t_minishell *ms)
{
	t_linebuffer	*lb;

	lb = ms->lb;
	if (lb->i_max >= lb->size - 1)
	{
		lb->buffer = bigger_calloc(lb->buffer, lb->size, LINE_BUFFER_SIZE);
		lb->size += LINE_BUFFER_SIZE;
	}
	if (lb->i == lb->i_max)
		lb->buffer[lb->i_max] = (char)c;
	else
	{
		ft_memmove(lb->buffer + lb->i + 1, lb->buffer + lb->i,
			lb->i_max - lb->i);
		lb->buffer[lb->i] = (char)c;
	}
	lb->i_max++;
	lb->i++;
}

void	set_linebuffer_to(char *str, t_minishell *ms)
{
	int				n_buffer_chunks;
	int				str_len;
	t_linebuffer	*lb;

	lb = ms->lb;
	linebuffer_clear(ms);
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

void	linebuffer_clear(t_minishell *ms)
{
	wrap_free(ms->lb->buffer);
	ft_bzero(ms->lb, sizeof(t_linebuffer));
}

void	linebuffer_delete_one(t_minishell *ms)
{
	t_linebuffer	*lb;
	char			**tc;

	lb = ms->lb;
	tc = ms->termcaps;
	if (lb->i > 0)
	{
		tputs(tc[MOVE_LEFT_ONE], 1, ft_putchar);
		tputs(tc[DELETE_CHAR], 1, ft_putchar);
		lb->i_max--;
		lb->i--;
		if (lb->i < lb->i_max)
			ft_memmove(lb->buffer + lb->i, lb->buffer + lb->i + 1,
				lb->i_max - lb->i);
		lb->buffer[lb->i_max] = '\0';
	}
}
