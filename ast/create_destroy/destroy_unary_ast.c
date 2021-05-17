/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_unary_ast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:18:05 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:19:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	destroy_unary_ast(t_ast *nnull_ast)
{
	destroy_block(nnull_ast->expr.unary.op_name);
	destroy_ast(&nnull_ast->expr.unary.target);
}
