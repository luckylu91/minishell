/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 10:43:44 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 11:08:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Operator content for a binary ast
t_block	*binary_op_at(t_ast *binary_ast)
{
	return (binary_ast->expr.binary.op_name);
}

// Left AST content for a binary ast
t_ast	*binary_left_at(t_ast *binary_ast)
{
	return (binary_ast->expr.binary.left);
}

// Right AST content for a binary ast
t_ast	*binary_right_at(t_ast *binary_ast)
{
	return (binary_ast->expr.binary.right);
}
