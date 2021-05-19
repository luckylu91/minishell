/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:58:23 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 17:40:29 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	before_exit(void *ms_ptr)
{
	t_minishell *ms;

	ms = ms_ptr;
	terminal_done();
	if (ms)
	{
		// if (write_histfile(ms->h) == -1)
		// 	ms->exit_code = -1;
		return (ms->exit_code);
	}
	else
		return (0);
}

void	exit_properly(void *ms_ptr)
{
	exit(before_exit(ms_ptr));
}

void	exit_with_code(int code, t_minishell *ms)
{
	ms->exit_code = code;
	exit_properly(ms);
}
