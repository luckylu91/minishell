#include "ast_api.h"

char *charpointer_str(char *str)
{
	if (str)
		return (ft_strdup(str));
	else
		return (ft_strdup("null_str"));
}

static char	*ast_type_str(t_ast *ast)
{
	t_ast_type type = ast->type;

	switch(type)
	{
		case string_expr:
			return (ft_strdup("string"));
		case text_expr:
			return (ft_strdup("text"));
		case redir_expr:
			return (ft_strdup("redir"));
		case unary_expr:
			return (ft_strdup("unary"));
		case binary_expr:
			return (ft_strdup("binary"));
		case command_expr:
			return (ft_strdup("command"));
		default:
			return (ft_strdup(""));
	}
}

static void	print_string_ast(t_ast *ast)
{
	print_block(ast->expr.string);
}

static void	print_text_ast(t_ast *ast)
{
	print_block_list(ast->expr.text);
}

static void	print_redir_ast(t_ast *ast)
{
	char *op_str = NULL;
	char *fname_str = NULL;

	op_str = charpointer_str(ast->expr.redir.redir_op);
	fname_str = charpointer_str(ast->expr.redir.file_name);

	printf("fd: %d | op: \"%s\" | fname: \"%s\"",
		ast->expr.redir.fildes,
		op_str,
		fname_str);
	free(op_str);
	free(fname_str);
}

// void	print_unary_ast(t_ast *ast)
// {

// }

// void	print_binary_ast(t_ast *ast)
// {

// }

// void	print_command_ast(t_ast *ast)
// {

// }

static void	print_ast_content(t_ast *ast)
{
	t_ast_type type = ast->type;

	switch(type)
	{
		case string_expr:
			print_string_ast(ast);
			break ;
		case text_expr:
			print_text_ast(ast);
			break ;
		case redir_expr:
			print_redir_ast(ast);
			break ;
		// case unary_expr:
		// 	return (ft_strdup("unary"));
		// case binary_expr:
		// 	return (ft_strdup("binary"));
		// case command_expr:
		// 	return (ft_strdup("command"));
		default:
	}
}

void	print_ast(t_ast *ast)
{
	char *type_str = NULL;
	char *content_str = NULL;

	if (!ast)
		return ;
	type_str = ast_type_str(ast);
	printf("(%s, ", type_str);
	print_ast_content(ast);
	printf(")");
}