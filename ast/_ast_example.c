#include "ast_api.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_ast	*new_ast_str(char *str)
{
	t_ast *ast;

	ast = calloc(sizeof(t_ast), 1);
	ast->type = string_expr;
	ast->expr.string = strdup(str);
	return (ast);
}

t_ast	*new_ast_unary(char *name, t_ast *target)
{
	t_ast					*ast;
	struct s_unary_expr	*expr;

	ast = calloc(1, sizeof(t_ast));
	ast->type = unary_expr;
	expr = &(ast->expr.unary);
	expr->op_name = strdup(name);
	expr->target = target;
	return (ast);
}


t_ast	*new_ast_binary(char *name, t_ast *left, t_ast *right)
{
	t_ast					*ast;
	struct s_binary_expr	*expr;

	ast = calloc(1, sizeof(t_ast));
	ast->type = binary_expr;
	expr = &(ast->expr.binary);
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
	strcat(res, s1);
	strcat(res, s2);
	return (res);
}

char	*full_concat_aggragation(t_ast *ast)
{
	char				*res;
	struct s_unary_expr	*uexpr;
	if (ast->type == string_expr)
		return (strdup(ast->expr.string));
	else if (ast->type == unary_expr)
	{
		uexpr = &(ast->expr.unary);
		if (strcmp(uexpr->op_name, "$") == 0 && uexpr->target->type == string_expr)
			return (getenv(uexpr->target->expr.string));
	}
	else if (ast->type == binary_expr)
		return (
			ft_strjoin(
				full_concat_aggragation(ast->expr.binary.left),
				full_concat_aggragation(ast->expr.binary.right)
			)
		);
	return (NULL);
}

int main()
{
	t_ast	*ast;
	char	*res;

	ast = new_ast_binary(
		"concatenate",
		new_ast_str("lalali"),
		new_ast_unary("$", new_ast_str("PATH"))
	);
	res = full_concat_aggragation(ast);
	if (!res)
		printf("Aggregation returned NULL\n");
	printf("%s\n", res);
}
