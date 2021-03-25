#include "ast.h"
#include <stdlib.h>

t_status parse_cmdseq(t_ast **ast, t_list *tokens)
{
	t_ast *ast_cmdchain;
	t_status status;

	parse_semicol(&tokens); // only advance if one is found
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
		(*tokens) = (*tokens)->next
		return (recognized);
	}
	return (not_recognized);
}

t_status parse_cmdchain(t_list **tokens, t_ast **cmdchain_ast)
{
	t_ast *cmd_ast;
	t_status status;
	t_block *chainop;

	*cmdchain_ast = NULL;
	status = status_ok;
	chainop = NULL;
	while (status == status_ok)
	{
		status = parse_cmd(tokens, &cmd_ast);
		if (!cmd_ast || status != status_ok)
			break;
		addback_cmd_ast(cmdchain_ast, chainop);
		lst_step(tokens);
		if (!is_chainop(*tokens))
			break ;
		chainop = block_dup(*tokens);
		lst_step(tokens);
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
	parse_text(tokens, &text_ast);
	if (!text_ast)
		return (unexpected_token_error(to_str(*tokens)));
	*cmd_ast = create_cmd_ast(text_ast);
	status = status_ok;
	while (status == status_ok)
	{
		status = parse_redir(tokens, &next_ast);
		if (status == status_ok && !next_ast)
			status = parse_text(tokens, &next_ast);
		if (!next_ast)
			break;
		addback_txt_redir_ast(cmd_ast, next_ast);
		skip_spaces(tokens);
	}
	if (status != status_ok)
		return (unexpected_token_error(*tokens));
	return (status_ok);
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
			lst_step(tokens, 2);
		}
		else
			return (unexpected_token_error(to_str((*tokens)->next)));
	}
	return (status_ok);
}

int is_text(t_list *tokens)
{
	t_block *token;

	token = token_at(tokens);
	if (!token->is_special || token->is_wildcard)
		return (1);
	return (0);
}

t_status	parse_text(t_list **tokens, t_ast **text_ast)
{
	skip_spaces(tokens); ////
	*text_ast = NULL;
	while (is_text(*tokens))
	{
		addback_text_ast(text_ast, *tokens);
		lst_step(tokens, 1);
	}
	return (status_ok);
}
