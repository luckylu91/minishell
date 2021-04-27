#include "execution.h"


int		exe_ast(t_ast *l_ast, int i, int *old_pipe)
{
	int	new_pipe[2];

	printf("debut exe_ast\n");
	if (!l_ast)
		return (1);
	if (l_ast->type == command_expr)
	{
		printf("wtf\n");
		if (i == 0)
			exe_cmd(l_ast, NULL, 0,NULL);
		else
			exe_cmd(l_ast, old_pipe, 1, NULL);
	}
	else if (l_ast->type == binary_expr)
	{
		pipe(new_pipe);
//		printf("ici ?\n");
		if (i == 0)
		{
			exe_ast(l_ast->expr.binary.left, 1, new_pipe);
//			printf("la ?\n");
			exe_cmd(l_ast->expr.binary.right, new_pipe, 2, NULL);
			l_ast->exit_code = l_ast->expr.binary.right->exit_code;

		}
		else
		{
			exe_ast(l_ast->expr.binary.left, 1, new_pipe);
			exe_cmd(l_ast->expr.binary.right,new_pipe,3,old_pipe);
			l_ast->exit_code = l_ast->expr.binary.right->exit_code;
		}
	}
	printf("fin exe_ast\n");
	return (1);
}

int exe_all(t_list *l_ast)
{
	if (l_ast == NULL)
		return (1);
	exe_ast(((t_ast*)(l_ast->content)), 0, NULL);
	exe_all(l_ast->next);
	printf("fin exe_all\n");
	return (1);	
}
