/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:33:09 by lzins             #+#    #+#             */
/*   Updated: 2021/05/10 14:20:54 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast_api.h"
#include "error.h"
#include "execution.h"
#include "terminal.h"
#include "hist.h"

typedef struct	s_linebuffer
{
	char	*buffer;
	int		i_max;
	int		i;
	int		size;
}				t_linebuffer;

typedef struct		s_minishell
{
	t_hist			*h;
	int				exit_code;
	char			**env;
	t_linebuffer	*lb;
	char			**termcaps;
	int				fd_in;
	int				fd_out;
	char			*tabintent;
	// char			*tab_path;
}	t_minishell;

t_minishell	g_global_var;

typedef struct	s_tabinfo
{
	char	*basedir;
	// char	*str_path;
	char	*str_to_complete;
	int		do_nothing;
}	t_tabinfo;

int		before_exit(void *ms_ptr);
void	exit_with_code(int code);
void	exit_properly(void *ms_ptr);
void	put_current_line(void);
int		process_line(char *line);

int		is_up_down_arrow(int c);
void	redirect_up_down(char* str);
int		is_left_right_arrow(int c);
int		redirect_left_right(char* str);
void	redirect_tab(void);

#endif
