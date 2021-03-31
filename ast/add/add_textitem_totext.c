/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textitem_totext.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:37:47 by lzins             #+#    #+#             */
/*   Updated: 2021/03/29 14:08:19 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

int	add_textitem_totext(t_ast **text_ast, t_block *block)
{
	t_block	*block_copy;

	// no need to protect text_ast
	if (!create_ast_if_needed(text_ast, text_expr))
		return (0);
	block_copy = dup_block(block);
	if (!block_copy)
		return (0);
	if (!ft_lstadd_back_content(&(*text_ast)->expr.text, block_copy))
	{
		destroy_block(block_copy);
		return (0);
	}
	return (1);
}
