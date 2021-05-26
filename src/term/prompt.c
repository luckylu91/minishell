/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:32:44 by lzins             #+#    #+#             */
/*   Updated: 2021/05/26 15:57:53 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

char				*our_getcwd(void);

#define CWD_COLOR		COLOR_BLUE
#define DOLLAR_COLOR	COLOR_RED

void	show_prompt(t_minishell *ms)
{
	char	*cwd_str;

	cwd_str = our_getcwd();
	tputs(tparm(ms->termcaps[COLOR_CAP], CWD_COLOR), 1, ft_putchar);
	ft_putstr_fd(cwd_str, STDOUT_FILENO);
	tputs(tparm(ms->termcaps[COLOR_CAP], DOLLAR_COLOR), 1, ft_putchar);
	ft_putstr_fd("$ ", STDOUT_FILENO);
	tputs(ms->termcaps[MODIF_ERASE_CAP], 1, ft_putchar);
	wrap_free(cwd_str);
}
