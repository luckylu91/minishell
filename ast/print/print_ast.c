#include "ast_api.h"

// char *charpointer_str(char *str)
// {
// 	if (str)
// 		return (ft_strdup(str));
// 	else
// 		return (ft_strdup("null_str"));
// }

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
	printf("(");
	print_block_list(ast->expr.text);
	printf(")");
}

static void	print_redir_ast(t_ast *ast)
{
	// op_str = charpointer_str(ast->expr.redir.redir_op);
	// fname_str = charpointer_str(ast->expr.redir.file_name);

	printf("(fd: %d | op: \"%s\" | fname: \"%s\")",
		ast->expr.redir.fildes,
		ast->expr.redir.redir_op->str,
		ast->expr.redir.file_name->str);
}

static void print_txt_ast_sep(void *txt_ast, void *sep)
{
	print_text_ast(txt_ast);
	ft_putstr_fd(sep, STDOUT_FILENO);
}

static void print_red_ast_sep(void *red_ast, void *sep)
{
	print_redir_ast(red_ast);
	ft_putstr_fd(sep, STDOUT_FILENO);
}

void	print_command_ast(t_ast *ast)
{
	printf("[[");
	ft_lstiter_arg(ast->expr.command.text_list, " ", print_txt_ast_sep);
	printf("END_ARGS / redirs : ");
	ft_lstiter_arg(ast->expr.command.redir_list, " ", print_red_ast_sep);
	printf("END_REDIRS]]");
}


// void	print_unary_ast(t_ast *ast)
// {

// }

// void	print_binary_ast(t_ast *ast)
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
		case command_expr:
			print_command_ast(ast);
			break ;
		default :
			break ;
	}
}

void	print_ast(t_ast *ast)
{
	char *type_str = NULL;
	char *content_str = NULL;

	if (!ast)
		return ;
	type_str = ast_type_str(ast);
	printf("{ast_type:%s, ", type_str);
	print_ast_content(ast);
	printf("}");
}
