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
		case text_expr:
			return (ft_strdup("text"));
		case redir_expr:
			return (ft_strdup("redir"));
		case binary_expr:
			return (ft_strdup("binary"));
		case command_expr:
			return (ft_strdup("command"));
		default:
			return (ft_strdup(""));
	}
}

static char	*text_string(t_list *block_lst)
{
	t_list	*char_blocks;
	char	*str;

	char_blocks = ft_lstmap(block_lst, block_string_ptr, wrap_free);
	str = ft_lststrjoin(char_blocks, ", ", "", "");
	ft_lstclear(&char_blocks, wrap_free);
	return (str);
}

static void	print_text_ast(t_list *block_lst)
{
	char	*str;

	str = text_string(block_lst);
	ft_putstr_fd(str, STDOUT_FILENO);
	wrap_free(str);
}

static char *redir_string(t_ast *ast)
{
	char	*str;
	char	*fname_str;

	fname_str = text_string(ast->expr.redir.file_name);
	asprintf(&str, "(fd: %d | op: \"%s\" | fname: \"%s\")",
		ast->expr.redir.fildes,
		ast->expr.redir.redir_op->str,
		fname_str);
	wrap_free(fname_str);
	return (str);
}

static void *redir_string_ptr(void *ast_ptr)
{
	return (redir_string((t_ast *)ast_ptr));
}

static void	print_redir_ast(t_ast *ast)
{
	// op_str = charpointer_str(ast->expr.redir.redir_op);
	// fname_str = charpointer_str(ast->expr.redir.file_name);
	char *str;

	str = redir_string(ast);
	ft_putstr_fd(str, STDOUT_FILENO);
	wrap_free(str);
}

void	print_command_ast(t_ast *ast)
{
	char *str_redirs;
	t_list	*char_redirs;

	char_redirs = ft_lstmap(ast->expr.command.redir_list, redir_string_ptr, wrap_free);
	str_redirs = ft_lststrjoin(char_redirs, " -> ", "", "");
	printf("cmd_args: ");
	print_text_ast(ast->expr.command.text_list);
	printf(" END_ARGS // cmd_redirs : %s END_REDIRS", str_redirs);
	ft_lstclear(&char_redirs, wrap_free);
	wrap_free(str_redirs);
}


// void	print_unary_ast(t_ast *ast)
// {

// }

void	print_binary_ast(t_ast *ast)
{
	printf("\n");
	print_ast(ast->expr.binary.left);
	printf("\n");
	print_block(ast->expr.binary.op_name);
	printf("\n");
	print_ast(ast->expr.binary.right);
	printf("\n");
}

static void	print_ast_content(t_ast *ast)
{
	t_ast_type type = ast->type;

	switch(type)
	{
		case text_expr:
			print_text_ast(ast->expr.text);
			break ;
		case redir_expr:
			print_redir_ast(ast);
			break ;
		// case unary_expr:
		// 	return (ft_strdup("unary"));
		case binary_expr:
			print_binary_ast(ast);
			break;
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

static void print_ast_ptr(void *ast_ptr)
{
	printf("---\n");
	print_ast((t_ast*)ast_ptr);
	printf("\n");
}

void	print_ast_list(t_list *ast_lst)
{
	if (!ast_lst)
		printf("---\nEMPTY_AST\n---\n");
	else
	{
		ft_lstiter(ast_lst, NULL, print_ast_ptr);
		printf("---\n");
	}
}
