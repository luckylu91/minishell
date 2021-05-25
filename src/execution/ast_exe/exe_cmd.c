#include "execution.h"
#include <sys/wait.h>

void	child_exe_not_builtin(t_all_str *chemin)
{
	int		path_fd;

	if (!chemin->path)
		chemin->path = chemin->all_var[0];
	path_fd = open(chemin->path, O_RDONLY);
	if (path_fd == -1)
	{
		bash_error_errno(chemin->path);
		exit(126);
	}
	close(path_fd);
}

void	child_exe(t_state_pipe sp, int* fd, t_all_str chemin,
	t_minishell *ms)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(chemin.all_var[0]))
		child_exe_not_builtin(&chemin);
	close_and_dup(sp, fd);
	setup_all_fd(fd);
	if (is_builtin(chemin.all_var[0]))
		exit(start_builtin(chemin.all_var, ms));
	else
		execve(chemin.path, chemin.all_var, ms->env);
}

int	cmd_notf(t_all_str chemin, t_minishell *ms, int *fd)
{
	pid_t	child;

	ms->exit_code = 127;
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_all_fd(fd);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(chemin.all_var[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (child);
}

int	no_pipe_exe(t_all_str chemin, t_state_pipe sp, int *fd,
	t_minishell *ms)
{
	int	temp;

	if (sp.state != 0)
	{
		if (sp.state > 1)
		{
			close(sp.both_pipe[0][1]);
			close(sp.both_pipe[0][0]);
		}
		return (-1);
	}
	else
	{
		temp = dup(2);
		if (fd[2] >= 0)
			dup2(fd[2], 2);
		ft_lstdupint_back(&ms->no_pipe_exit_codes,
			start_builtin(chemin.all_var, ms));
		dup2(temp, 2);
		close(temp);
		return (0);
	}
}

int	exe_cmd(t_ast *cmd, int **both_pipe, int state, t_minishell *ms)
{
	int				fd[256];
	t_state_pipe	sp;
	pid_t			child;
	t_all_str		chemin;

	setup_var_exe(fd, &sp, state, both_pipe);
	setup_redir(cmd, fd);
	setup_chemin(&chemin, cmd, ms);
	if (!chemin.path && !is_builtin(chemin.all_var[0])
		&& !is_builtin_nopipe(chemin.all_var[0])
		&& !contains_slash(chemin.all_var[0]))
		return (cmd_notf(chemin, ms, fd));
	if (is_builtin_nopipe(chemin.all_var[0]))
		return (no_pipe_exe(chemin, sp, fd, ms));
	child = fork();
	if (child == 0)
		child_exe(sp, fd, chemin, ms);
	closing(sp, fd);
	return (child);
}
