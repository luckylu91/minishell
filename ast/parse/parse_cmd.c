/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:04 by lzins             #+#    #+#             */
/*   Updated: 2021/04/06 13:43:16 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "ast_api.h"

t_status	parse_cmd(t_ast **cmd_ast, t_list **tokens)
{
	t_ast	*next_ast;
	t_status status;

	*cmd_ast = NULL;
	// parse_text(&next_ast, tokens);
	// if (!next_ast)
	// 	return (unexpected_token_error(*tokens));
	// if (add_textredir_tocmd(cmd_ast, next_ast) == -1)
	// 	return (-1);
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
