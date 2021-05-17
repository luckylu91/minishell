#include "execution.h"

extern t_minishell g_global_var;
int		exe_ast(t_ast *l_ast, int i, int *old_pipe,t_list **all_child)
{
	int	new_pipe[2];

//	printf("debut exe_ast\n");
	if (!l_ast)
		return (1);
	if (l_ast->type == command_expr)
	{
	//	printf("wtf %p\n",all_child);
	//	if (*all_child == NULL)
	//		printf("mon cul\n");
		if (i == 0)
		{
	//		printf("ici \n");
			ft_lstdupint_back(all_child, exe_cmd(l_ast, NULL, 0,NULL));
		}
			else
			ft_lstdupint_back(all_child, exe_cmd(l_ast, old_pipe, 1, NULL));
	}
	else if (l_ast->type == binary_expr)
	{
		pipe(new_pipe);
//		printf("ici ?\n");
		if (i == 0)
		{
			exe_ast(l_ast->expr.binary.left, 1, new_pipe, all_child);
//			printf("la ?\n");
			ft_lstdupint_back(all_child,exe_cmd(l_ast->expr.binary.right, new_pipe, 2, NULL));
			l_ast->exit_code = l_ast->expr.binary.right->exit_code;

		}
		else
		{
			exe_ast(l_ast->expr.binary.left, 1, new_pipe, all_child);
			ft_lstdupint_back(all_child,exe_cmd(l_ast->expr.binary.right,new_pipe,3,old_pipe));
			l_ast->exit_code = l_ast->expr.binary.right->exit_code;
		}
	}
//	printf("fin exe_ast\n");
	return (1);
}
