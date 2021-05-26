/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:08:26 by lzins             #+#    #+#             */
/*   Updated: 2021/05/26 17:01:45 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_printable(char c, t_minishell *ms)
{
	linebuffer_add_insert(c, ms);
	tputs(ms->termcaps[INSERT_MODE], 1, ft_putchar);
	ft_putchar_fd((char)c, STDOUT_FILENO);
	tputs(ms->termcaps[INSERT_EXIT], 1, ft_putchar);
}

static void	process_newline(t_minishell *ms)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	process_line(ms->lb->buffer, ms);
	linebuffer_clear(ms);
	rewind_hist(ms->h);
	show_prompt(ms);
}

void	process_char(int c, t_minishell *ms)
{
	if (ft_isprint(c))
		process_printable(c, ms);
	else if (c == '\x7f')
		linebuffer_delete_one(ms);
	else if (c == '\x9')
		redirect_tab(ms);
	else if (c == '\n')
		process_newline(ms);
	else if (is_up_down_arrow(c))
		redirect_up_down((char *)&c, ms);
	else if (is_left_right_arrow(c))
		redirect_left_right((char *)&c, ms);
}
