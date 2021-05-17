/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:00 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:23:41 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	parse_text(t_ast **text_ast, t_list **tokens)
{
	skip_spaces(tokens);
	*text_ast = NULL;
	while (*tokens && !is_eof_lst(*tokens) && is_text_lst(*tokens))
	{
		add_textitem_totext(text_ast, block_at(*tokens));
		*tokens = ft_lststep(*tokens, 1);
	}
}
