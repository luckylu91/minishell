/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:33:09 by lzins             #+#    #+#             */
/*   Updated: 2021/05/06 13:58:48 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast_api.h"
#include "error.h"
#include "execution.h"
#include "terminal.h"
#include "hist.h"

typedef struct	s_minishell
{
	t_hist	*h;
	int		exit_code;
	char	**env;
}	t_minishell;

t_minishell	g_global_var;

void	exit_properly(void *ms_ptr);
void	put_current_line(t_linebuffer *lb, t_hist *h, int fd_out);
int		process_line(char *line);

int		is_up_down_arrow(int c);
void	redirect_up_down(char* str, t_hist *h, t_linebuffer *lb, char **tc, int fd_out);
int		is_left_right_arrow(int c);
int		redirect_left_right(char* str, t_linebuffer *lb, char **tc);

#endif
