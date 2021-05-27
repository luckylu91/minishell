#include "execution.h"
#include <sys/wait.h>
#include <sys/errno.h>

void	child_exe_not_builtin(t_all_str *chemin)
{
	int		path_fd;

	if (!chemin->path)
		chemin->path = chemin->all_var[0];
	path_fd = open(chemin->path, O_RDONLY);
	if (path_fd == -1)
	{
		bash_error_errno(chemin->path);
		destroy_chemin(*chemin);
		exit(126);
	}
	close(path_fd);
}

void	child_exe(t_state_pipe sp, int *fd, t_all_str chemin,
		t_minishell *ms)
{
	int	err;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(chemin.all_var[0])
		&& !is_builtin_nopipe(chemin.all_var[0]))
		child_exe_not_builtin(&chemin);
	close_and_dup(sp, fd);
	setup_all_fd(fd);
	if (is_builtin(chemin.all_var[0]) || is_builtin_nopipe(chemin.all_var[0]))
	{
		wrap_free(chemin.path);
		exit(start_builtin(chemin.all_var, ms));
	}
	else
		err = execve(chemin.path, chemin.all_var, ms->env);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	destroy_chemin(chemin);
	exit(126);
}

int	cmd_notf(t_all_str chemin, t_minishell *ms, int *fd)
{
	pid_t	child;

	ms->exit_code = exception(chemin.all_var[0]);
	if (ms->exit_code == 0)
		ms->exit_code = 127;
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_all_fd(fd);
		error_msg_all(chemin.all_var[0], ms->exit_code);
		destroy_chemin(chemin);
		exit(ms->exit_code);
	}
	destroy_chemin(chemin);
	return (child);
}

int	no_pipe_exe(t_all_str chemin, int *fd,
		t_minishell *ms)
{
	int save[256];

	save_fd(save, fd);
	ft_lstdupint_back(&ms->no_pipe_exit_codes,
		start_builtin(chemin.all_var, ms));
	restore_fd(save, fd);
	wrap_free(chemin.path);
	return (0);
}

int	exe_cmd(t_ast *cmd, int **both_pipe, int state, t_minishell *ms)
{
	int				fd[257];
	t_state_pipe	sp;
	pid_t			child;
	t_all_str		chemin;

	setup_var_exe(fd, &sp, state, both_pipe);
	if (setup_redir(cmd, fd, sp, ms) == -1)
		return (-1);
	setup_chemin(&chemin, cmd, ms);
	if ((!chemin.path && !is_builtin(chemin.all_var[0])
			&& !is_builtin_nopipe(chemin.all_var[0])
			&& !contains_slash(chemin.all_var[0]))
		|| exception(chemin.all_var[0]))
		return (cmd_notf(chemin, ms, fd));
	if (is_builtin_nopipe(chemin.all_var[0]) && state == 0)
		return (no_pipe_exe(chemin, fd, ms));
	child = fork();
	if (child == 0)
		child_exe(sp, fd, chemin, ms);
	closing(sp, fd);
	destroy_chemin(chemin);
	return (child);
}
