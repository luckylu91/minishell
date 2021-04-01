/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_tochain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:46:51 by lzins             #+#    #+#             */
/*   Updated: 2021/04/01 23:48:52 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

int add_cmd_tochain(t_ast **cmdchain_ast, t_ast *cmd_ast, t_block *chainop)
{
	t_ast	*parent;
	t_block	*chainop_copy;

	if (!*cmdchain_ast)
	{
		*cmdchain_ast = cmd_ast;
		return (1);
	}
	parent = NULL;
	if (create_ast(&parent, binary_expr) == -1) // to change (create_binary_ast)
		return (-1);
	chainop_copy = dup_block(chainop);
	if (!chainop_copy)
	{
		free(chainop_copy);
		return (-1);
	}
	parent->expr.binary.left = *cmdchain_ast;
	parent->expr.binary.op_name = chainop_copy;
	parent->expr.binary.right = cmd_ast;
	*cmdchain_ast = parent;
	return (1);
}
