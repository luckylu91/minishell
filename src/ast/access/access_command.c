/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 10:49:22 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 11:15:10 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Command's text list (cmd name and args as blocks) of a command ast
t_list	*cmd_text_list_at(t_ast *cmd_ast)
{
	return (cmd_ast->expr.command.text_list);
}

// Command's redirections of a command ast
t_list	*cmd_redir_list_at(t_ast *cmd_ast)
{
	return (cmd_ast->expr.command.redir_list);
}

// Set text list of a command ast
void	set_cmd_text_list(t_ast *cmd_ast, t_list *text_list)
{
	cmd_ast->expr.command.text_list = text_list;
}

// Set redir list of a command ast
void	set_cmd_redir_list(t_ast *cmd_ast, t_list *redir_list)
{
	cmd_ast->expr.command.redir_list = redir_list;
}
