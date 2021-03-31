/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:19:57 by lzins             #+#    #+#             */
/*   Updated: 2021/03/31 11:57:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "ast_api.h"

t_status parse_redir(t_ast **redir_ast, t_list **tokens)
{
	skip_spaces(tokens); //// ???? et si les espaces etaient important : utilser autre variable tokens_moving
	*redir_ast = NULL;
	if (is_redirop_lst(*tokens))
	{
		if (is_text_lst((*tokens)->next))
		{
			if (!new_redir_ast(redir_ast, block_at(*tokens),
					block_at((*tokens)->next)))
				return (STATUS_ERROR);
			*tokens = ft_lststep(*tokens, 2);
		}
		else
			return (unexpected_token_error((*tokens)->next));
	}
	return (STATUS_OK);
}
