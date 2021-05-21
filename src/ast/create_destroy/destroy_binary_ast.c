/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_binary_ast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:18:16 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:19:11 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	destroy_binary_ast(t_ast *nnull_ast)
{
	destroy_block(nnull_ast->expr.binary.op_name);
	destroy_ast(&nnull_ast->expr.binary.left);
	destroy_ast(&nnull_ast->expr.binary.right);
}
