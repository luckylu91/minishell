#include "execution.h"

void	binary_exe(t_ast *l_ast, int i, int **both_pipe, t_minishell *mini)
{
	int		state;
	pid_t	child_pid;

	if (i == 0)
		state = 2;
	else
		state = 3;
	exe_ast(binary_left_at(l_ast), 1, both_pipe[0], mini);
	child_pid = exe_cmd(binary_right_at(l_ast), both_pipe, state, mini);
	ft_lstdupint_back(&(mini->all_child), child_pid);
	l_ast->exit_code = binary_right_at(l_ast)->exit_code;
}

int	exe_ast(t_ast *l_ast, int i, int *old_pipe, t_minishell *mini)
{
	int		*both_pipe[2];
	int		new_pipe[2];
	pid_t	child_pid;

	both_pipe[1] = old_pipe;
	if (!l_ast)
		return (1);
	if (l_ast->type == command_expr)
	{
		if (i == 0)
			child_pid = exe_cmd(l_ast, NULL, 0, mini);
		else
			child_pid = exe_cmd(l_ast, both_pipe, 1, mini);
		ft_lstdupint_back(&(mini->all_child), child_pid);
	}
	else if (l_ast->type == binary_expr)
	{
		pipe(new_pipe);
		both_pipe[0] = new_pipe;
		binary_exe(l_ast, i, both_pipe, mini);
	}
	return (1);
}
