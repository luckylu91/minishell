/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_left_right.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:10:19 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 16:11:16 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_left_right_arrow(int c)
{
	char *c_chars;

	c_chars = (char*)&c;
	return (ft_strncmp(c_chars, "\x1b[", 2) == 0
			&& (c_chars[2] == 'C' || c_chars[2] == 'D'));
}

int	redirect_left_right(char* str, t_minishell *ms)
{
	int				left_pressed;

	left_pressed = (str[2] == 'D');
	if (left_pressed && ms->lb->i > 0)
	{
		tputs(tparm(ms->termcaps[MOVE_LEFT], 1), 1, ft_putchar);
		ms->lb->i--;
	}
	else if (!left_pressed && ms->lb->i < ms->lb->i_max)
	{
		tputs(tparm(ms->termcaps[MOVE_RIGHT], 1), 1, ft_putchar);
		ms->lb->i++;
	}
	return (1);
}
