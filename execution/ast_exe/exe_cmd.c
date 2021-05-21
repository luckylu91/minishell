#include "execution.h"
#include <sys/wait.h>

void	signal_interrupt_caca(int signum)
{
	if (signum == SIGINT)
		exit(130);
	if (signum == SIGQUIT)
		exit(131);
	exit(0);
}

void	child_exe( state_pipe sp, both_fd fd, all_str chemin, t_minishell *ms)
{
	 signal(SIGINT, signal_interrupt_caca);
	 signal(SIGQUIT, signal_interrupt_caca);
//	signal(SIGINT, SIG_DFL);
//	signal(SIGQUIT, SIG_DFL);
	close_and_dup(sp, fd);
	if (fd.int_in != -1)
		dup2(fd.int_in, fd.in->expr.redir.fildes);
	if (fd.int_out != -1)
		dup2(fd.int_out, fd.out->expr.redir.fildes);
	if (is_builtin(chemin.all_var[0]))
		exit(start_builtin(chemin.all_var, ms));
	else
		execve(chemin.path, chemin.all_var, ms->env);
}

void	cmd_notf(all_str chemin, t_minishell *ms, both_fd fd)
{
	pid_t	child;

	ms->exit_code = 127;
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd.int_in != -1)
			dup2(fd.int_in, fd.in->expr.redir.fildes);
		if (fd.int_out != -1)
			dup2(fd.int_out, fd.out->expr.redir.fildes);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(chemin.all_var[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(0);
	}
}

int	no_pipe_exe(all_str chemin, state_pipe sp, both_fd fd, t_minishell *ms)
{
	int	temp;

	if (sp.state != 0)
	{
		if (sp.state > 0)
		{
			if (sp.state != 1)
			{
				close(sp.both_pipe[0][1]);
				close(sp.both_pipe[0][0]);
			}
		}	
		return (-1);
	}
	else
	{
		temp = dup(2);
		if (fd.int_out == 2)
			dup2(fd.int_out, 2);
		ms->exit_code = start_builtin(chemin.all_var, ms);
		dup2(temp, 2);
		close(temp);
		return (1);
	}
}

int	exe_cmd(t_ast *cmd, int **both_pipe, int state, t_minishell *ms)
{
	both_fd		fd;
	state_pipe	sp;
	pid_t		child;
	all_str		chemin;

	setup_var_exe(&fd, &sp, state, both_pipe);
	if ((get_redir_fd(&fd, cmd->expr.command.redir_list)) < 0)
		return (-1);
	if (cmd->expr.command.text_list == NULL || check_redir(&fd))
		return (-1);
	setup_chemin(&chemin, cmd);
	if (chemin.path == NULL && is_builtin(chemin.all_var[0]) == 0
		&& is_builtin_nopipe(chemin.all_var[0]) == 0)
	{
		cmd_notf(chemin, ms, fd);
		return (-1);
	}
	if (is_builtin_nopipe(chemin.all_var[0]))
		return (no_pipe_exe(chemin, sp, fd, ms));
	child = fork();
	if (child == 0)
		child_exe(sp, fd, chemin, ms);
	closing(sp, fd);
	return (child);
}
