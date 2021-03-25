#ifndef AST_H
#define AST_H

typedef struct	s_ast
{
	enum e_type
	{
		string_expr, unary_expr, binary_expr, command_expr
	}	type;
	union u_expr
	{
		char				*string_expr;
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
			char			*cmd_name;
			struct t_list	*arg_list;
			struct t_list	*redir_list;
		}					command_expr;
		struct				s_redir_expr
		{
			int				fildes; //    doivent etre ensenble lors de la tokenisation
			char			*redir_op; // doivent etre ensenble lors de la tokenisation
			char			*target;
		}
	}						expr;

}				t_ast;

#endif
