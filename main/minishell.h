/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:33:09 by lzins             #+#    #+#             */
/*   Updated: 2021/05/20 10:27:26 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast_api.h"
#include "error.h"
#include "execution.h"
#include "terminal.h"
#include "hist.h"

t_minishell	g_global_var;

void	signal_interrupt(int signum);
int		before_exit(void *ms_ptr);
void	exit_with_code(int code, t_minishell *ms);
void	exit_properly(void *ms_ptr);
void	process_char(int c, t_minishell *ms);
int		process_line(char *line, t_minishell *ms);
int		process_line_test(char *line, t_minishell *ms);

int		is_up_down_arrow(int c);
void	redirect_up_down(char* str, t_minishell *ms);
int		is_left_right_arrow(int c);
int		redirect_left_right(char* str, t_minishell *ms);
void	redirect_tab(t_minishell *ms);

#endif
