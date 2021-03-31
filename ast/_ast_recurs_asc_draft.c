/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_recurs_asc_draft.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:58:23 by lzins             #+#    #+#             */
/*   Updated: 2021/03/29 14:41:19 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_status	unexpected_token_error(char *token)
{
	ft_putstr_fd("syntax error: unnexpected token '", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'.", STDERR_FILENO);
	return (STATUS_ERROR);
}

t_status parse_cmdseq(t_ast **ast, t_list *tokens)
{
	t_ast *ast_cmdchain;
	t_status status;

	identify_semicol(&tokens); // only advance if one is found
	*ast = NULL;
	if (!create_ast(&ast, binary_expr))
		return (STATUS_ERROR);
	while (tokens)
		if (parse_cmdchain(&tokens, &ast_cmdchain) != STATUS_OK)
			return (STATUS_ERROR);
		if (is_eof_lst(tokens))
			return (STATUS_OK);
		if (!identify_semicol(tokens))
			return (unexpected_token_error(to_str(*tokens)));
	return (STATUS_OK);
}

int identify_semicol(t_list **tokens)
{
	if (is_semicol_lst(*tokens))
	{
		ft_lststep(tokens, 1);
		return (1);
	}
	return (0);
}

t_status parse_cmdchain(t_ast **cmdchain_ast, t_list **tokens)
{
	t_ast *cmd_ast;
	t_status status;
	t_block *chainop;

	*cmdchain_ast = NULL;
	status = STATUS_OK;
	chainop = NULL;
	while (status == STATUS_OK)
	{
		status = parse_cmd(&cmd_ast, tokens);
		if (!cmd_ast || status != STATUS_OK)
			break;
		add_cmd_tochain(cmdchain_ast, cmd_ast, chainop);
		ft_lststep(tokens, 1);
		if (!is_chainop(*tokens))
			break ;
		chainop = dup_block(*tokens);
		ft_lststep(tokens, 1);
	}
	return (status);
}

t_status parse_cmd(t_ast **cmd_ast, t_list **tokens)
{
	t_ast	*next_ast;
	t_status status;

	*cmd_ast = NULL;
	if (is_beg(*tokens))
		identify_semicolon(tokens);
	parse_text(&next_ast, tokens);
	if (!next_ast)
		return (unexpected_token_error(to_str(*tokens)));
	if (add_textredir_tocmd(cmd_ast, next_ast) == -1)
		return (-1);
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

t_status parse_redir(t_ast **redir_ast, t_list **tokens)
{
	skip_spaces(tokens); //// ???? et si les espaces etaient important : utilser autre variable tokens_moving
	*redir_ast = NULL;
	if (is_redirop_lst(*tokens))
	{
		if (is_text((*tokens)->next))
		{
			if (!new_redir_ast(redir_ast, *tokens, (*tokens)->next))
				return (STATUS_ERROR);
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
	if (!is_special_lst(token) || is_wildcard_lst(token))
		return (1);
	return (0);
}

t_status	parse_text(t_ast **text_ast, t_list **tokens)
{
	skip_spaces(tokens); ////
	*text_ast = NULL;
	while (is_text(*tokens))
	{
		add_textitem_totext(text_ast, *tokens);
		ft_lststep(tokens, 1);
	}
	return (STATUS_OK);
}
