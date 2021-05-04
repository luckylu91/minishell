/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_special_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:03 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 12:19:44 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int		is_up_down_arrow(int c)
{
	char *c_chars;

	c_chars = (char*)&c;
	return (ft_strncmp(c_chars, "\x1b[", 2) == 0
			&& (c_chars[2] == 'A' || c_chars[2] == 'B' || ft_all_in(c_chars + 2, "ABCD")));
}

int	redirect_special(char* str, t_hist *h)
{
	int		up_pressed;

	up_pressed = (str[2] == 'A');
	if ((h->position_state == BOTTOM && !up_pressed)
			|| !h->hlines)
		return (0);
	if (up_pressed)
		move_hist(h, 1);
	else
		move_hist(h, -1);
	printf("Current hist line : %s\n", get_hist_line(h));
	return (1);
}
