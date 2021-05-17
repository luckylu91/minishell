/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textredir_tocmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:08:59 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:13:16 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

static t_list	**text_list(t_ast *cmd_ast)
{
	return (&cmd_ast->expr.command.text_list);
}

static t_list	**redir_list(t_ast *cmd_ast)
{
	return (&cmd_ast->expr.command.redir_list);
}

void	add_textredir_tocmd(t_ast **cmd_ast, t_ast *text_redir_ast)
{
	if (!*cmd_ast)
		*cmd_ast = create_ast(command_expr);
	if (text_redir_ast->type == text_expr)
	{
		if (*text_list(*cmd_ast))
			addback_space_block(text_list(*cmd_ast));
		ft_lstadd_back(text_list(*cmd_ast), text_redir_ast->expr.text);
		wrap_free(text_redir_ast);
	}
	else if (text_redir_ast->type == redir_expr)
		ft_lstadd_back_content(redir_list(*cmd_ast), text_redir_ast);
}
