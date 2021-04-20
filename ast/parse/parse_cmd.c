/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:04 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 11:55:44 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "ast_api.h"

t_status	parse_cmd(t_ast **cmd_ast, t_list **tokens)
{
	t_ast		*next_ast;
	t_status	status;

	*cmd_ast = NULL;
	status = STATUS_OK;
	while (status == STATUS_OK)
	{
		status = parse_redir(&next_ast, tokens);
		if (status == STATUS_OK && !next_ast)
			status = parse_text(&next_ast, tokens);
		if (!next_ast)
			break;
		add_textredir_tocmd(cmd_ast, next_ast);
		skip_spaces(tokens);
	}
	if (status != STATUS_OK)
		return (unexpected_token_error(*tokens));
	return (STATUS_OK);
}

t_status	parse_cmd_block_list(t_ast **cmd_ast, t_list **tokens)
{
	t_ast		*next_redir;
	t_list		*text_block_list;
	t_list		*next_text;
	t_status	status;

	*cmd_ast = NULL;
	status = STATUS_OK;
	while (status == STATUS_OK)
	{
		status = parse_redir(&next_redir, tokens);
		next_text = NULL;
		if (status == STATUS_OK && !next_redir)
			status = parse_text_block_lst(&next_text, tokens);
		if (next_redir && !add_textredir_tocmd(cmd_ast, next_redir))
			return (STATUS_ERROR);
		else if (next_text)
		{
			if (!create_ast_if_needed(cmd_ast, command_expr))
			{
				ft_lstclear(next_text, destroy_block);
				return (STATUS_ERROR);
			}
			t_list **cmd_text_list;
			cmd_text_list = &(*cmd_ast)->expr.command.text_list;
			if (*cmd_text_list && !addback_space_block(cmd_text_list))
			{
				ft_lstclear(next_text, destroy_block);
				return (STATUS_ERROR);
			}
			if (!ft_lstadd_back_content(cmd_text_list, next_text))
			{
				ft_lstclear(next_text, destroy_block);
				return (STATUS_ERROR);
			}
		}
		else
			break ;
		skip_spaces(tokens);
	}
	if (status != STATUS_OK)
		return (unexpected_token_error(*tokens));
	return (STATUS_OK);
}
