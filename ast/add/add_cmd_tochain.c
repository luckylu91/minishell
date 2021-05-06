/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_tochain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:46:51 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 15:37:28 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	add_cmd_tochain(t_ast **cmdchain_ast, t_ast *cmd_ast, t_block *chainop)
{
	t_ast	*parent;
	t_block	*chainop_copy;

	if (!*cmdchain_ast)
	{
		*cmdchain_ast = cmd_ast;
		return ;
	}
	parent = NULL;
	parent = create_ast(binary_expr); // to change (create_binary_ast)
	chainop_copy = dup_block(chainop);
	parent->expr.binary.left = *cmdchain_ast;
	parent->expr.binary.op_name = chainop_copy;
	parent->expr.binary.right = cmd_ast;
	*cmdchain_ast = parent;
}
