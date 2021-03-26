/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_recurs_asc_draft.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:58:23 by lzins             #+#    #+#             */
/*   Updated: 2021/03/26 11:41:37 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"
#include "block_api.h"

t_status parse_cmdseq(t_ast **ast, t_list *tokens)
{
	t_ast *ast_cmdchain;
	t_status status;

	identify_semicol(&tokens); // only advance if one is found
	status = in_progress;
	*ast = NULL;
	while (*tokens)
		status = parse_cmdchain(ast, &tokens);
		if (is_eof(tokens));
		if (identify_semicol(tokens) == recognized)
			continue;
		break;
	return (status);
}

int identify_semicol(t_list **tokens)
{
	if (is_semicol(*tokens))
	{
		ft_lststep(tokens, 1);
		return (1);
	}
	return (0);
}

t_status parse_cmdchain(t_list **tokens, t_ast **cmdchain_ast)
{
	t_ast *cmd_ast;
	t_status status;
	t_block *chainop;

	*cmdchain_ast = NULL;
	status = STATUS_OK;
	chainop = NULL;
	while (status == STATUS_OK)
	{
		status = parse_cmd(tokens, &cmd_ast);
		if (!cmd_ast || status != STATUS_OK)
			break;
		addback_cmd_ast(cmdchain_ast, chainop);
		ft_lststep(tokens, 1);
		if (!is_chainop(*tokens))
			break ;
		chainop = dup_block(*tokens);
		ft_lststep(tokens, 1);
	}
	return (status);
}

t_status parse_cmd(t_list **tokens, t_ast **cmd_ast)
{
	t_ast	*next_ast;
	t_status status;

	*cmd_ast = NULL;
	if (is_beg(*tokens))
		identify_semicolon(tokens);
	parse_text(tokens, &next_ast);
	if (!next_ast)
		return (unexpected_token_error(to_str(*tokens)));
	*cmd_ast = create_cmd_ast(next_ast);
	status = STATUS_OK;
	while (status == STATUS_OK)
	{
		status = parse_redir(tokens, &next_ast);
		if (status == STATUS_OK && !next_ast)
			status = parse_text(tokens, &next_ast);
		if (!next_ast)
			break;
		addback_txt_redir_ast(cmd_ast, next_ast);
		skip_spaces(tokens);
	}
	if (status != STATUS_OK)
		return (unexpected_token_error(*tokens));
	return (STATUS_OK);
}

t_status parse_redir(t_list **tokens, t_ast **redir_ast)
{
	skip_spaces(tokens); //// ???? et si les espaces etaient important : utilser autre variable tokens_moving
	*redir_ast = NULL;
	if (is_redirop(*tokens))
	{
		if (is_text((*tokens)->next))
		{
			*redir_ast = create_redir_ast(*tokens, (*tokens)->next);
			ft_lststep(tokens, 2);
		}
		else
			return (unexpected_token_error(to_str((*tokens)->next)));
	}
	return (STATUS_OK);
}

int is_text(t_list *tokens)
{
	t_block *token;

	token = token_at(tokens);
	if (!is_special(token) || is_wildcard(token))
		return (1);
	return (0);
}

t_status	parse_text(t_list **tokens, t_ast **text_ast)
{
	skip_spaces(tokens); ////
	*text_ast = NULL;
	while (is_text(*tokens))
	{
		addback_textblock_ast(text_ast, *tokens);
		ft_lststep(tokens, 1);
	}
	return (STATUS_OK);
}
