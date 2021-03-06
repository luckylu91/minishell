/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_api.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:16:01 by lzins             #+#    #+#             */
/*   Updated: 2021/05/26 17:16:40 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_API_H
# define AST_API_H

# include "libft.h"
# include "block_api.h"
# include "ast.h"
# include "ast_add.h"
# include "ast_alloc.h"
# include "ast_parse.h"
# include "errors.h"
# include <stdio.h>
# include <stdlib.h>

t_list	*text_at(t_ast *text_ast);
int		redir_fd_at(t_ast *redir_ast);
t_block	*redir_op_at(t_ast *redir_ast);
char	*redir_op_str_at(t_ast *redir_ast);
t_list	*redir_fname_at(t_ast *redir_ast);
int		redir_is_ambiguous(t_ast *redir_ast);
t_list	*cmd_text_list(t_ast *cmd_ast);
t_list	*cmd_redir_list(t_ast *cmd_ast);
void	set_cmd_text_list(t_ast *cmd_ast, t_list *text_list);
void	set_cmd_redir_list(t_ast *cmd_ast, t_list *redir_list);
t_block	*binary_op(t_ast *binary_ast);
t_ast	*binary_left(t_ast *binary_ast);
t_ast	*binary_right(t_ast *binary_ast);

#endif