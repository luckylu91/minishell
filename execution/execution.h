/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:02:41 by lzins             #+#    #+#             */
/*   Updated: 2021/05/19 16:28:49 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "libft.h"
#include "searchdir.h"
#include "minishell_types.h"
#include "error.h"
#include "to_block.h"
#include <fcntl.h>
#include "ast_api.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define	ASSIGN_NONE		0
#define	ASSIGN_EQUAL	1
#define	ASSIGN_PEQUAL	2

typedef struct s_both_fd
{
	t_ast *in;
	int int_in;
	int int_out;
	t_ast *out;
}				both_fd;
typedef struct s_all_str
{
	char	**all_path;
	char	**all_var;
	char	*path;
}				all_str;
typedef struct s_state_pipe
{
	int	state;
	int **both_pipe;
}				state_pipe;
char	*get_char_from_block(t_list *l);
void	dup_str(t_list *l, char **res, int i);
int		size_list(t_list *l);
char **from_list_to_str_tab(t_list *l);
int		is_last(t_list *l, char c);
int		start_builtin(char **c, t_minishell *m);
int		is_builtin(char *c);
int		is_builtin_nopipe(char *c);
int		check_redir(both_fd *fd);
int		get_redir_fd(both_fd *res, t_list *l);
int		export(char **argv, char ***our_env);
int		find_var(char *arg, char **env);
int		our_unset(char **argv, char ***our_env);
int		our_env(char **tab_env);
int		our_echo(char **argv);
int		our_pwd(char **argv);
int		our_cd(char **argv, char **env);
int		is_assign_operator(char *s);
int		assign_operator_offset(char *arg);
int		not_valid_identifier_error(char *arg);
char	*strdup_remove_plus(char *src, int op_index);

char	*search_env(char *str, char **env);
void	our_getenv(t_block *block, char **res_addr, t_minishell *ms);
char	*our_getcwd(void);
void	replace_unquoted(t_block *env_block, t_list **replacement, t_minishell *ms);
void	replace_dquoted(t_block *env_block, t_list **replacement, t_minishell *ms);
int		replace_env(t_ast *cmdchain_ast, t_minishell *ms);
char	**split_path(void);
int		exe_all(t_list *l_staticast);
int		copy_environ(char ***new_env_addr);
int		exe_ast(t_ast *l_ast, int i, int *pipe, t_minishell *mini);
void	insert_in_list(t_list **lst_prev, t_list *lst, t_list *insert,
	t_list **begin);
int		remove_spaces(t_list *block_lst, t_list **new_block_lst);
int		remove_spaces_cmdchain(t_ast *cmdchain_ast);

int		exe_cmd(t_ast *cmd, int **both_pipe, int state, t_minishell *global );

#endif
