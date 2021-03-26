/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:16:22 by lzins             #+#    #+#             */
/*   Updated: 2021/03/26 14:09:04 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

int	create_ast(t_ast **result_ast, t_ast_type type)
{
	*result_ast = ft_calloc(1, sizeof(t_ast));
	if (!*result_ast)
		return (0);
	(*result_ast)->type = type;
	return (1);
}

int	create_ast_if_needed(t_ast **result_ast, t_ast_type type)
{
	if (!*result_ast && !create_ast(type, result_ast))
		return (0);
	return (1);
}

int create_string_ast(t_ast **result_ast, t_block *string_block)
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

// NOT NEEDED BECAUSE WONT BE CREATED THIS WAY, THE CODE OF THIS WILL BE IN SOME OTHER PROCEDURE
// int create_text_ast(t_ast **result_ast, t_list *text_blocks)
// {
// 	t_list *text_blocks_moving;

// 	*result_ast = NULL;
// 	while (text_blocks_moving)
// 	{
// 		if (!add_textitem_totext(&result_ast, text_blocks_moving))
// 			return (0);
// 		text_blocks_moving = text_blocks_moving->next;
// 	}
// 	if (!create_ast_if_needed(result_ast, text_expr))
// 		return (0);
// 	return (1);
// }

int create_cmd_ast(t_ast **result_ast, t_ast *text_ast)
{
	*result_ast = NULL;
	if (!text_ast || text_ast->type != text_expr)
	{
		printf("Error creating cmd ast from something other than a text expression\n"); // debug
		return (0);
	}
	if (!create_ast(result_ast, command_expr))
		return (0);
	if (!add_textredir_tocmd(result_ast, text_ast))
		return(0);
	return (1);
}
