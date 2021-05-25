#include "execution.h"
#include <sys/wait.h>
#include <sys/errno.h>

extern int errno;

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
	int err;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if (!is_builtin(chemin.all_var[0])  && !is_builtin_nopipe(chemin.all_var[0]))
		child_exe_not_builtin(&chemin);
	close_and_dup(sp, fd);
	setup_all_fd(fd);
	if (is_builtin(chemin.all_var[0]) || is_builtin_nopipe(chemin.all_var[0]))
	{
		exit(start_builtin(chemin.all_var, ms));
	}
	else
		err =execve(chemin.path, chemin.all_var, ms->env);
	if (err == -1)
	{
		printf("err\n");
		ft_putstr_fd(strerror(errno),2);
		ft_putstr_fd("\n",2);
	}
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
		exit(ms->exit_code);
	}
	return (child);
}

int	no_pipe_exe(t_all_str chemin, int *fd,
	t_minishell *ms)
{
	int	temp;

	temp = dup(2);
	if (fd[2] >= 0)
		dup2(fd[2], 2);
	ft_lstdupint_back(&ms->no_pipe_exit_codes,
		ms->exit_code = start_builtin(chemin.all_var, ms));
	dup2(temp, 2);
	close(temp);
	return (0);
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
	/* printf("!%s! {%s} |%i| %i %i %i \n",chemin.all_var[0],chemin.path,!chemin.path,!is_builtin(chemin.all_var[0]) */
		/* , !is_builtin_nopipe(chemin.all_var[0]) */
		/* , !contains_slash(chemin.all_var[0])); */
	if ((!chemin.path && !is_builtin(chemin.all_var[0])
		&& !is_builtin_nopipe(chemin.all_var[0])
		&& !contains_slash(chemin.all_var[0])) || exception(chemin.all_var[0])) 
		return (cmd_notf(chemin, ms, fd));
	if (is_builtin_nopipe(chemin.all_var[0]) && state == 0)
		return (no_pipe_exe(chemin, fd, ms));
	child = fork();
	if (child == 0)
		child_exe(sp, fd, chemin, ms);
	closing(sp, fd);
	return (child);
}
