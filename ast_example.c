#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_ast	*new_ast_str(char *str)
{
	t_ast *ast;

	ast = calloc(sizeof(t_ast), 1);
	ast->type = string_expr;
	ast->expr.string_expr = strdup(str);
	return (ast);
}

t_ast	*new_ast_binary(char *name, t_ast *left, t_ast *right)
{
	t_ast					*ast;
	struct s_binary_expr	*expr;

	ast = calloc(1, sizeof(t_ast));
	ast->type = binary_expr;
	expr = &(ast->expr.binary_expr);
	expr->op_name = strdup(name);
	expr->left = left;
	expr->right = right;
	return (ast);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len_tot;

	len_tot = strlen(s1) + strlen(s2);
	res = calloc(len_tot + 1, sizeof(char));
	fflush(stdout);
	strcat(res, s1);
	strcat(res, s2);
	return (res);
}

char	*full_concat_aggragation(t_ast *ast)
{
	char *res;
	if (ast->type == string_expr)
		return (strdup(ast->expr.string_expr));
	else if (ast->type == binary_expr)
		return (
			ft_strjoin(
				full_concat_aggragation(ast->expr.binary_expr.left),
				full_concat_aggragation(ast->expr.binary_expr.right)
			)
		);
}

int main()
{
	t_ast *ast;

	ast = new_ast_binary(
		"concatenate",
		new_ast_str("lalali"),
		new_ast_str("lilalo")
	);
	printf("%s\n", full_concat_aggragation(ast));
}
