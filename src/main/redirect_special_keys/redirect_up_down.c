/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_up_down.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:06:41 by lzins             #+#    #+#             */
/*   Updated: 2021/05/26 19:12:56 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_up_down_arrow(int c)
{
	char	*c_chars;

	c_chars = (char *)&c;
	return (ft_strncmp(c_chars, "\x1b[", 2) == 0
		&& (c_chars[2] == 'A' || c_chars[2] == 'B'));
}

static void	clear_current_line(t_minishell *ms)
{
	if (!ms->lb->buffer)
		return ;
	while (ms->lb->i-- > 0)
		tputs(ms->termcaps[MOVE_LEFT_ONE], 1, ft_putchar);
	while (ms->lb->i_max-- > 0)
		tputs(ms->termcaps[DELETE_CHAR], 1, ft_putchar);
}

void	redirect_up_down(char *str, t_minishell *ms)
{
	int	up_pressed;

	up_pressed = (str[2] == 'A');
	if (!ms->h->hlines || (!up_pressed && ms->h->position_state == BOTTOM))
		return ;
	if (up_pressed)
		move_hist(ms->h, 1);
	else
		move_hist(ms->h, -1);
	clear_current_line(ms);
	set_linebuffer_to(get_hist_line(ms->h), ms);
	if (ms->lb->buffer)
		ft_putstr_fd(ms->lb->buffer, STDOUT_FILENO);
}
