/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_interrupt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:09:39 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 18:45:52 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_interrupt(int signum)
{
	t_minishell	*ms;

	ms = ft_get_set_context(NULL);
	if (signum == SIGINT)
	{
		linebuffer_clear(ms);
		rewind_hist(ms->h);
		ft_putchar_fd('\n', STDOUT_FILENO);
		if (!ms->all_child)
			show_prompt(ms);
	}
	if (ms->all_child)
	{
		ms->exit_code = 128 + signum;
		if (signum == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	}
}
