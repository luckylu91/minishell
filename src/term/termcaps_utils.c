/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:20:34 by lzins             #+#    #+#             */
/*   Updated: 2021/05/05 16:39:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	ft_putchar(int c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	return (0);
}

void	ft_putstr(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
}

// void	clear_line(char **tc)
// {
// 	tputs(tc[CLEAR_CAP], 1, ft_putchar);
// }

// void	move_to(char **tc, int i, int j)
// {
// 	tputs(tgoto(tc[MOVE_CAP], i, j), 1, ft_putchar);
// }
