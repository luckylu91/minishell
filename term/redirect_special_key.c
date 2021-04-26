/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_special_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:03 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 11:52:50 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	print_escape_sequence(char *str, int fd)
{
	unsigned i = 0;

	while (i < 4 && str[i])
	{
		if (str[i] == '\x1b')
			ft_putstr_fd("ESC", fd);
		else
			ft_putchar_fd(str[i], fd);
		++i;
	}
}

void	redirect_special(char* str, int fd)
{
	if (str[0] == '\x1b' && str[1] == '[')
	{
		if (str[2] == 'A')
			ft_putstr_fd("UP", fd);
		if (str[2] == 'B')
			ft_putstr_fd("DOWN", fd);
		if (str[2] == 'C')
			ft_putstr_fd("RIGHT", fd);
		if (str[2] == 'D')
			ft_putstr_fd("LEFT", fd);
	}
}
