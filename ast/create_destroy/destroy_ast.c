/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:10:43 by lzins             #+#    #+#             */
/*   Updated: 2021/03/29 15:28:44 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	destroy_string_ast(t_ast *nnull_ast)
{
	destroy_block(nnull_ast->expr.string);
}

void	destroy_text_ast(t_ast *nnull_ast)
{
	destroy_block_lst(&nnull_ast->expr.text);
}

void	destroy_redir_ast(t_ast *nnull_ast)
{
	destroy_block(nnull_ast->expr.redir.redir_op);
	destroy_block(nnull_ast->expr.redir.file_name);
}

void	destroy_unary_ast(t_ast *nnull_ast)
{
	destroy_block(nnull_ast->expr.unary.op_name);
	destroy_ast(&nnull_ast->expr.unary.target);
}

void	destroy_binary_ast(t_ast *nnull_ast)
{
	destroy_block(nnull_ast->expr.binary.op_name);
	destroy_ast(&nnull_ast->expr.binary.left);
	destroy_ast(&nnull_ast->expr.binary.right);
}

static void destroy_text_ast_ptr(void *p)
{
	destroy_text_ast((t_ast*)p);
}

static void destroy_redir_ast_ptr(void *p)
{
	destroy_redir_ast((t_ast*)p);
}

void	destroy_command_ast(t_ast *nnull_ast)
{
	ft_lstclear(&nnull_ast->expr.command.text_list, destroy_text_ast_ptr);
	ft_lstclear(&nnull_ast->expr.command.redir_list, destroy_redir_ast_ptr);
}

void	destroy_ast(t_ast **ast)
{
	if (!*ast)
		return ;
	(*ast)->destruct(*ast);
	*ast = NULL;
}

// void destroy_ast(t_ast *ast)
// {
// 	if (!ast)
// 		return ;
// 	if (ast->type == string_expr)
// 		destroy_string_ast(ast);
// 	else if (ast->type == text_expr)
// 		destroy_string_ast(ast);
// 	else if (ast->type == redir_expr)
// 		destroy_string_ast(ast);
// 	else if (ast->type == string_expr)
// 		destroy_string_ast(ast);
// 	else if (ast->type == string_expr)
// 		destroy_string_ast(ast);
// 	else if (ast->type == string_expr)
// 		destroy_string_ast(ast);
// }
