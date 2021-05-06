/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_special_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:03 by lzins             #+#    #+#             */
/*   Updated: 2021/05/06 11:45:50 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_up_down_arrow(int c)
{
	char *c_chars;

	c_chars = (char*)&c;
	return (ft_strncmp(c_chars, "\x1b[", 2) == 0
			&& (c_chars[2] == 'A' || c_chars[2] == 'B'));
}

int		is_left_right_arrow(int c)
{
	char *c_chars;

	c_chars = (char*)&c;
	return (ft_strncmp(c_chars, "\x1b[", 2) == 0
			&& (c_chars[2] == 'C' || c_chars[2] == 'D'));
}

void	clear_current_line(t_linebuffer *lb, t_hist *h, char **tc)
{
	int		len_screen;

	if (!lb->buffer)
		len_screen = 0;
	else
		len_screen = ft_strlen(lb->buffer);
	tputs(tparm(tc[MOVE_LEFT], len_screen), 1, ft_putchar);
	for (int k = 0; k < len_screen; k++)
		tputs(tc[DELETE_CHAR], 1, ft_putchar);
	// tputs(tc[MOVE_LEFT_ONE], 1, ft_putchar);
	// tputs(tc[DELETE_MODE], 1, ft_putchar);
	// tputs(tc[DELETE_CHAR], 1, ft_putchar);
	// tputs(tc[MODIF_ERASE_CAP], 1, ft_putchar);
}

void	redirect_up_down(char* str, t_hist *h, t_linebuffer *lb, char **tc, int fd_out)
{
	char	*line;
	int		up_pressed;

	up_pressed = (str[2] == 'A');
	if ((h->position_state == BOTTOM && !up_pressed) || !h->hlines)
			//|| !h->hlines || (h->hlines && !h->hlines->next && up_pressed))
		return ;
	if (up_pressed)
		move_hist(h, 1);
	else
		move_hist(h, -1);
	clear_current_line(lb, h, tc);
	set_linebuffer_to(lb, get_hist_line(h));
	if (lb->buffer)
		ft_putstr_fd(lb->buffer, fd_out);
	// put_current_line(lb, h, fd_out);
	// printf("\nCurrent hist line = '%s'\n", get_hist_line(h));
}

int	redirect_left_right(char* str, t_linebuffer *lb, char **tc)
{
	int		left_pressed;

	left_pressed = (str[2] == 'D');
	if (left_pressed && lb->i > 0)
	{
		tputs(tparm(tc[MOVE_LEFT], 1), 1, ft_putchar);
		lb->i--;
	}
	else if (!left_pressed && lb->i < lb->i_max)
	{
		tputs(tparm(tc[MOVE_RIGHT], 1), 1, ft_putchar);
		lb->i++;
	}
	return (1);
}
