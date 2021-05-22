/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:19:57 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 20:20:13 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_status	parse_redir(t_ast **redir_ast, t_list **tokens)
{
	t_block		*redirop;
	t_ast		*file_name_ast;

	skip_spaces(tokens);
	*redir_ast = NULL;
	if (is_redirop_lst(*tokens))
	{
		redirop = block_at(*tokens);
		if (!(*tokens)->next)
			return (STATUS_ERROR);
		*tokens = ft_lststep(*tokens, 1);
		skip_spaces(tokens);
		if (!is_text_lst(*tokens))
			return (STATUS_ERROR);
		parse_text(&file_name_ast, tokens);
		*redir_ast = new_redir_ast(redirop, text_at(file_name_ast));
		wrap_free(file_name_ast);
	}
	return (STATUS_OK);
}
