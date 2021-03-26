/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textitem_totext.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:37:47 by lzins             #+#    #+#             */
/*   Updated: 2021/03/26 10:06:43 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

int	add_textitem_totext(t_ast **text_ast, t_list *item_lst)
{
	t_block	*item;
	t_block	*item_copy;

	// no need to protect text_ast
	if (!create_ast_if_needed(text_expr, text_ast))
		return (0);
	item = block_at(item_lst);
	item_copy = dup_block(item);
	if (!item_copy)
		return (0);
	if (!ft_lstadd_back_content(&(*text_ast)->expr.text_expr, item_copy))
	{
		block_destroy(item_copy);
		return (0);
	}
	return (1); 
}
