/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:58:23 by lzins             #+#    #+#             */
/*   Updated: 2021/05/06 13:58:35 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_global_var;

void	exit_properly(void *ms_ptr)
{
	t_minishell *ms;

	ms = ms_ptr;
	terminal_done();
	if (ms)
	{
		if (write_histfile(ms->h) == -1)
			ms->exit_code = -1;
		exit(ms->exit_code);
	}
	else
		exit(0);
}