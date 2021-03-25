/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:36:10 by lzins             #+#    #+#             */
/*   Updated: 2021/03/25 14:36:22 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
#define AST_H

#include "libft.h"

typedef struct	s_ast
{
	enum e_type
	{
		string_expr, text_expr, redir_expr,
		unary_expr, binary_expr, command_expr
	}	type;
	union u_expr
	{
		t_block				*string_expr;
		t_list				*text_expr; // t_block list
		struct				s_redir_expr
		{
			int				fildes;
			char			*redir_op;
			char			*file_name;
		}					redir_expr;
		struct				s_unary_expr
		{
			char			*op_name;
			struct s_ast	*target;
		}					unary_expr;
		struct				s_binary_expr
		{
			char			*op_name;
			struct s_ast	*left;
			struct s_ast	*right;
		}					binary_expr;
		struct				s_command_expr
		{
			t_list			*text_list; // ast::text_expr list
			t_list			*redir_list; // ast::redir_expr list
		}					command_expr;
	}						expr;

}				t_ast;

#endif
