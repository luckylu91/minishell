/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textredir_tocmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:08:59 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 11:47:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

static t_list **text_list(t_ast *cmd_ast)
{
	return (&cmd_ast->expr.command.text_list);
}

static t_list **redir_list(t_ast *cmd_ast)
{
	return (&cmd_ast->expr.command.redir_list);
}

int	add_textredir_tocmd(t_ast **cmd_ast, t_ast *text_redir_ast)
{
	if (!create_ast_if_needed(cmd_ast, command_expr))
		return (0);
	// non NULL of text_redir_ast checked before in parse_cmd
	if (text_redir_ast->type == text_expr
		&& !ft_lstadd_back_content(text_list(*cmd_ast), text_redir_ast))
			return (0);
	if (text_redir_ast->type == redir_expr
		&& !ft_lstadd_back_content(redir_list(*cmd_ast), text_redir_ast))
			return (0);
	return (1);
}
