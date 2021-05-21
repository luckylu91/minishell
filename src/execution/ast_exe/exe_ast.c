#include "execution.h"

void	binary_exe(t_ast *l_ast, int i, int **both_pipe, t_minishell *mini)
{
	if (i == 0)
	{
		exe_ast(l_ast->expr.binary.left, 1, both_pipe[0], mini);
		ft_lstdupint_back(&(mini->all_child),
			exe_cmd(l_ast->expr.binary.right, both_pipe, 2, mini));
		l_ast->exit_code = l_ast->expr.binary.right->exit_code;
	}
	else
	{
		exe_ast(l_ast->expr.binary.left, 1, both_pipe[0], mini);
		ft_lstdupint_back(&(mini->all_child),
			exe_cmd(l_ast->expr.binary.right, both_pipe, 3, mini));
		l_ast->exit_code = l_ast->expr.binary.right->exit_code;
	}
}

int	exe_ast(t_ast *l_ast, int i, int *old_pipe, t_minishell *mini)
{
	int	*both_pipe[2];
	int	new_pipe[2];

	both_pipe[1] = old_pipe;
	if (!l_ast)
		return (1);
	if (l_ast->type == command_expr)
	{
		if (i == 0)
			ft_lstdupint_back(&(mini->all_child),
				exe_cmd(l_ast, NULL, 0, mini));
		else
			ft_lstdupint_back(&(mini->all_child),
				exe_cmd(l_ast, both_pipe, 1, mini));
	}
	else if (l_ast->type == binary_expr)
	{
		pipe(new_pipe);
		both_pipe[0] = new_pipe;
		binary_exe(l_ast, i, both_pipe, mini);
	}
	return (1);
}
