/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:16:22 by lzins             #+#    #+#             */
/*   Updated: 2021/03/29 15:36:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

int	create_ast(t_ast **result_ast, t_ast_type type)
{
	*result_ast = ft_calloc(1, sizeof(t_ast));
	if (!*result_ast)
		return (0);
	(*result_ast)->type = type;
	if (type == string_expr)
		(*result_ast)->destruct = destroy_string_ast;
	else if (type == text_expr)
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

int	new_string_ast(t_ast **result_ast, t_block *string_block)
{
	t_block *string_block_copy;

	*result_ast = NULL;
	if (!create_ast(result_ast, string_expr))
		return (0);
	string_block_copy = dup_block(string_block);
	if (!string_block_copy)
		return (0);
	(*result_ast)->expr.string = string_block_copy;
	return (1);
}

int	new_redir_ast(t_ast **result_ast, t_block *redir_op, t_block *file_name)
{
	int	fd;
	char	*symbol_begin;
	t_block *redir_op_copy;
	t_block *file_name_copy;

	*result_ast = NULL;
	if (!create_ast(result_ast, redir_expr))
		return (0);
	parse_redirop(redir_op, &fd, &symbol_begin);
	redir_op_copy = create_block(spe, symbol_begin);
	file_name_copy = dup_block(file_name);
	(*result_ast)->expr.redir.fildes = fd;
	(*result_ast)->expr.redir.file_name = file_name_copy;
	(*result_ast)->expr.redir.redir_op = redir_op_copy;
	if (!file_name_copy || !redir_op_copy)
		return (0);
	return (1);
}

// int	create_text_ast(t_ast **result_ast)
// {
// 	if (!create_ast(result_ast, text_expr))
// 		return (0);
// 	(*result_ast)->destruct = destroy_text_ast;
// }

// int	create_cmd_ast(t_ast **result_ast, t_ast *text_ast)
// {
// 	*result_ast = NULL;
// 	if (!text_ast || text_ast->type != text_expr)
// 	{
// 		printf("Error creating cmd ast from something other than a text expression\n"); // debug
// 		return (0);
// 	}
// 	if (!create_ast(result_ast, command_expr))
// 		return (0);
// 	if (!add_textredir_tocmd(result_ast, text_ast))
// 		return(0);
// 	return (1);
// }

// NOT NEEDED, USE create_ast(_if_needed)

// int	create_unary_ast(t_ast **result_ast, t_block *op_name, t_ast *target) // target can be NULL ?
// {
// 	t_block	*op_name_copy;

// 	*result_ast = NULL;
// 	if (!op_name)
// 	{
// 		printf("missing operator name or target in create_unary_ast\n"); // debug
// 		return (0);
// 	}
// 	if (!create_ast(result_ast, unary_expr))
// 		return (0);
// 	op_name_copy = dup_block(op_name);
// 	if (!op_name_copy)
// 		return (0);
// 	(*result_ast)->expr.unary.op_name = op_name_copy;
// 	(*result_ast)->expr.unary.target = target;
// 	(*result_ast)->destruct = destroy_unary_ast;
// }


