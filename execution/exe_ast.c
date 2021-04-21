#include "execution.h"


int		exe_ast(t_ast *l_ast, int i, int *old_pipe)
{
	int	new_pipe[2];

	if (l_ast->type == command_expr)
	{
		if (i == 0)
			exe_cmd(l_ast,NULL,0);
		else
			exe_cmd(l_ast,NULL,2);
	}
	else if (l_ast->type == binary_expr)
	{
		pipe(new_pipe);
		printf("ici ?\n");
		if (i == 0)
		{

			printf("la ?\n");
			exe_cmd(l_ast->expr.binary.left,new_pipe,1);

		}
		else
		{
			dup2(old_pipe[1], new_pipe[0]);
			exe_cmd(l_ast->expr.binary.left,new_pipe,3);
		}
		exe_ast(l_ast->expr.binary.right, 1,new_pipe);
	}
	return (1);
}

int exe_all(t_list *l_ast)
{
	if (l_ast == NULL)
		return (1);
	exe_ast(((t_ast*)(l_ast->content)), 0, NULL);
	exe_all(l_ast->next);
	return (1);	
}
