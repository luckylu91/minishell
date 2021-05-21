/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_interrupt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:09:39 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 20:30:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	kill_all_children(t_minishell *ms, int signum)
{
	t_list	*child_lst;

	child_lst = ms->all_child;
	while (child_lst)
	{
		// TODO
		printf("Killing %d in the name of...\n", *(int *)(child_lst->content));
		kill(*(int *)(child_lst->content), signum);
		child_lst = child_lst->next;
	}
}

void	signal_interrupt(int signum)
{
	t_minishell	*ms;

	ms = ft_get_set_context(NULL);
	linebuffer_clear(ms);
	rewind_hist(ms->h);
	if (signum == SIGQUIT)
		ft_putstr_fd("^\\Quit: 3", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	show_prompt(ms);
	ms->prompted_signal = 1;
	kill_all_children(ms, signum);
}
