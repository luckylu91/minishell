/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:16:22 by lzins             #+#    #+#             */
/*   Updated: 2021/05/25 15:51:43 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_ast	*create_ast(t_ast_type type)
{
	t_ast	*result_ast;

	result_ast = ft_calloc(1, sizeof(t_ast));
	result_ast->type = type;
	if (type == text_expr)
		result_ast->destruct = destroy_text_ast;
	else if (type == redir_expr)
		result_ast->destruct = destroy_redir_ast;
	else if (type == command_expr)
		result_ast->destruct = destroy_command_ast;
	else if (type == binary_expr)
		result_ast->destruct = destroy_binary_ast;
	return (result_ast);
}

// t_ast	*create_ast_if_needed(t_ast_type type)
// {
// 	t_ast *result_ast;

// 	if (!result_ast)
// 		return (create_ast(type));
// 	return (result_ast);
// }

t_ast	*new_redir_ast(t_block *redir_op, t_list *file_name)
{
	int		fd;
	char	*symbol_begin;
	t_block	*redir_op_copy;
	t_ast	*result_ast;

	result_ast = create_ast(redir_expr);
	parse_redirop(redir_op, &fd, &symbol_begin);
	redir_op_copy = create_block(spe, symbol_begin);
	result_ast->expr.redir.ambiguous_error = 0;
	result_ast->expr.redir.fildes = fd;
	result_ast->expr.redir.file_name = file_name;
	result_ast->expr.redir.redir_op = redir_op_copy;
	return (result_ast);
}
