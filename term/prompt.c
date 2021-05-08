/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:32:44 by lzins             #+#    #+#             */
/*   Updated: 2021/05/08 17:01:33 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

char				*our_getcwd(void);

#define CWD_COLOR		COLOR_BLUE
#define DOLLAR_COLOR	COLOR_RED

void	show_prompt(void)
{
	char	*cwd_str;
	char	**tc;
	int		fd_out;

	tc = g_global_var.termcaps;
	fd_out = g_global_var.fd_out;
	cwd_str = our_getcwd();
	tputs(tparm(tc[COLOR_CAP], CWD_COLOR), 1, ft_putchar);
	ft_putstr_fd(cwd_str, fd_out);
	tputs(tparm(tc[COLOR_CAP], DOLLAR_COLOR), 1, ft_putchar);
	ft_putstr_fd("$ ", fd_out);
	tputs(tc[MODIF_ERASE_CAP], 1, ft_putchar);
}