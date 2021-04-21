/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:16:22 by lzins             #+#    #+#             */
/*   Updated: 2021/04/21 15:53:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

int	create_ast(t_ast **result_ast, t_ast_type type)
{
	*result_ast = ft_calloc(1, sizeof(t_ast));
	if (!*result_ast)
		return (0);
	(*result_ast)->type = type;
	if (type == text_expr)
		(*result_ast)->destruct = destroy_text_ast;
	else if (type == redir_expr)
		(*result_ast)->destruct = destroy_redir_ast;
	else if (type == command_expr)
		(*result_ast)->destruct = destroy_command_ast;
	else if (type == unary_expr)
		(*result_ast)->destruct = destroy_unary_ast;
	else if (type == binary_expr)
		(*result_ast)->destruct = destroy_binary_ast;
	return (1);
}

int	create_ast_if_needed(t_ast **result_ast, t_ast_type type)
{
	if (!*result_ast && !create_ast(result_ast, type))
		return (0);
	return (1);
}

int	new_redir_ast(t_ast **result_ast, t_block *redir_op, t_list *file_name)
{
	int		fd;
	char	*symbol_begin;
	t_block	*redir_op_copy;

	*result_ast = NULL;
	if (!create_ast(result_ast, redir_expr))
		return (0);
	parse_redirop(redir_op, &fd, &symbol_begin);
	redir_op_copy = create_block(spe, symbol_begin);
	(*result_ast)->expr.redir.ambiguous_error = 0;
	(*result_ast)->expr.redir.fildes = fd;
	(*result_ast)->expr.redir.file_name = file_name;
	(*result_ast)->expr.redir.redir_op = redir_op_copy;
	return (1);
}
