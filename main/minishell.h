/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:33:09 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 15:08:13 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "ast_api.h"
#include "error.h"
#include "execution.h"
#include "terminal.h"
#include "hist.h"


int process_line(char *line, t_hist *h);
typedef struct s_global_var
{
	int exit_code;
	char **env;
}			t_global_var;

typedef struct	s_mini_context
{
	t_hist	*h;
	int		exit_code;
}	t_mini_context;

#endif
