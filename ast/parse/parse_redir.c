/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:19:57 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 14:47:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "ast_api.h"

t_status parse_redir(t_ast **redir_ast, t_list **tokens)
{
	t_block		*redirop;
	t_ast		*file_name_ast;
	t_status	ret;

	skip_spaces(tokens); //// ???? et si les espaces etaient important : utilser autre variable tokens_moving
	*redir_ast = NULL;
	ret = STATUS_OK;
	if (is_redirop_lst(*tokens))
	{
		redirop = block_at(*tokens);
		*tokens = ft_lststep(*tokens, 1);
		skip_spaces(tokens);
		if (parse_text(&file_name_ast, tokens) == STATUS_ERROR)
			return (unexpected_token_error((*tokens)->next));
		if (!new_redir_ast(redir_ast, redirop, file_name_ast->expr.text))
			ret = STATUS_ERROR;
		free(file_name_ast);
		// if (is_text_lst((*tokens)))
		// {
		// 	if (!new_redir_ast(redir_ast, block_at(*tokens),
		// 			block_at((*tokens))))
		// 		return (STATUS_ERROR);
		// 	*tokens = ft_lststep(*tokens, 1);
		// }
		// else
		// 	return (unexpected_token_error((*tokens)->next));
	}
	return (ret);
}

// t_status	parse_redir_block_list(t_ast **redir_ast, t_list **tokens)
// {
// 	t_block	*redirop;
// 	t_list	*file_name;

// 	skip_spaces(tokens); //// ???? et si les espaces etaient important : utilser autre variable tokens_moving
// 	if (is_redirop_lst(*tokens))
// 	{
// 		redirop = block_at(*tokens);
// 		*tokens = ft_lststep(*tokens, 1);
// 		skip_spaces(tokens);
// 		if (parse_text_block_lst(&file_name, tokens) == STATUS_ERROR)
// 			return (unexpected_token_error((*tokens)->next));
// 		if (!new_redir_ast(redir_ast, redirop, file_name))
// 				return (STATUS_ERROR);
// 	}
// 	return (STATUS_OK);
// }
