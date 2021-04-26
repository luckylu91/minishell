/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:02:41 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 17:22:47 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "libft.h"
#include "searchdir.h"
#include "error.h"
#include "to_block.h"
#include <fcntl.h>
#include "ast_api.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

// mettre dans minishell.h (structure si besoin...)
int	g_exit_code;

int	export(char **argv, char ***our_env);
int	our_getenv(t_block *block, char **res_addr);
int	replace_unquoted(t_block *env_block, t_list **replacement);
int	replace_dquoted(t_block *env_block, t_list **replacement);
int	replace_env(t_ast *cmdchain_ast);
char	**split_path(void);
int	exe_all(t_list *l_ast);
int exe_ast(t_ast *l_ast, int i, int *pipe);
void insert_in_list(t_list **lst_prev, t_list *lst, t_list *insert,
		t_list **begin);
int	remove_spaces(t_list *block_lst, t_list **new_block_lst);
int	remove_spaces_cmdchain(t_ast *cmdchain_ast);

int	exe_cmd(t_ast *cmd, int *pipe, int state, int *old_pipe);
 typedef struct s_both_fd
 {
 	t_ast *in;
	int int_in;
	int int_out;
	t_ast *out;
 }				both_fd;


#endif
