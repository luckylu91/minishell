/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textitem_totext.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:37:47 by lzins             #+#    #+#             */
/*   Updated: 2021/05/05 09:46:17 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	add_textitem_totext(t_ast **text_ast, t_block *block)
{
	t_block	*block_copy;

	// no need to protect text_ast
	if (!*text_ast)
		*text_ast = create_ast(text_expr);
	block_copy = dup_block(block);
	ft_lstadd_back_content(&(*text_ast)->expr.text, block_copy);
}
