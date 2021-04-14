/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:19:57 by lzins             #+#    #+#             */
/*   Updated: 2021/04/06 14:38:31 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "ast_api.h"

t_status parse_redir(t_ast **redir_ast, t_list **tokens)
{
	t_block	*redirop;
	t_ast	*file_name;

	skip_spaces(tokens); //// ???? et si les espaces etaient important : utilser autre variable tokens_moving
	*redir_ast = NULL;
	if (is_redirop_lst(*tokens))
	{
		redirop = block_at(*tokens);
		*tokens = ft_lststep(*tokens, 1);
		skip_spaces(tokens);
		if (parse_text(&file_name, tokens) == STATUS_ERROR)
			return (unexpected_token_error((*tokens)->next));
		if (!new_redir_ast(redir_ast, redirop, file_name))
				return (STATUS_ERROR);
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
	return (STATUS_OK);
}
