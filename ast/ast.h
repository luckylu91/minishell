/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:36:10 by lzins             #+#    #+#             */
/*   Updated: 2021/04/22 11:55:20 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
#define AST_H

typedef enum	{
	STATUS_OK, STATUS_ERROR
}	t_status;

typedef enum	e_ast_type
{
	text_expr, redir_expr,
	unary_expr, binary_expr, command_expr
}				t_ast_type;

typedef struct	s_ast
{
	t_ast_type				type;
	union u_expr
	{
		t_list				*text; // t_block list (now with spaces)
		struct				s_unary_expr
		{
			t_block			*op_name;
			struct s_ast	*target;
		}					unary;
		struct				s_binary_expr
		{
			t_block			*op_name;
			struct s_ast	*left;
			struct s_ast	*right;
		}					binary;
		struct				s_command_expr
		{
			t_list			*text_list; // t_block list (before env replacement), then char* list
			t_list			*redir_list; // redir_expr list
		}					command;
		struct				s_redir_expr
		{
			int				ambiguous_error;
			int				fildes; //    doivent etre ensenble lors de la tokenisation
			t_block			*redir_op; // doivent etre ensenble lors de la tokenisation
			t_list			*file_name; // t_block list (before env replacement), then char* list (length one)
		}					redir;
	}						expr;
	void					(*destruct)(struct s_ast *self);
}				t_ast;

#endif
