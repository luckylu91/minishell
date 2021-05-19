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

int	exe_cmd(t_ast *cmd, int **both_pipe, int state, t_minishell *ms)
{
	char **all_path;
	both_fd fd;
	char **all_var;
	int status;
	char* path;
	pid_t child;

	all_var = from_list_to_str_tab(cmd->expr.command.text_list); 
	fd.in = NULL;
	fd.out = NULL;
	fd.int_in = -1;
	fd.int_out = -1;
	if ((get_redir_fd(&fd, cmd->expr.command.redir_list)) < 0)
		return (-1);
	all_path = split_path();
	if (cmd->expr.command.text_list == NULL)
		return (-1);
	if (check_redir(&fd))
		return (-1);
	path = search_cmd(all_path,all_var[0]); 
	if (path == NULL && is_builtin(all_var[0]) == 0 && is_builtin_nopipe(all_var[0]) == 0)
	{
		ms->exit_code = 127;
		child = fork();
		if (child == 0)
		{
			if (fd.int_in != -1)
				dup2(fd.int_in, fd.in->expr.redir.fildes);
			if (fd.int_out != -1)
				dup2(fd.int_out, fd.out->expr.redir.fildes);
			ft_putstr_fd("bash: ",2);
			ft_putstr_fd(all_var[0],2);
			ft_putstr_fd(": command not found\n",2);
			exit(0);
		}
		return (-1);
	}
	if (is_builtin_nopipe(all_var[0]) && state != 0)
	{	
		if (state >0)
		{
			if (state != 1)
			{
				close(both_pipe[0][1]);
				close(both_pipe[0][0]);
			}
		}	
		return (-1);
	}
	else if (is_builtin_nopipe(all_var[0]))
	{
		ms->exit_code = start_builtin(all_var, ms);
		return (1);
	}
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, signal_interrupt_caca);
		signal(SIGQUIT, signal_interrupt_caca);
		// signal(SIGQUIT, SIG_DFL);

		if (state == 1 && fd.out == NULL)
		{
			dup2(both_pipe[1][1],STDOUT_FILENO);
			close(both_pipe[1][0]);
			close(both_pipe[1][1]);
		}
		if (state == 3 && fd.out == NULL)
		{
			dup2(both_pipe[1][1], STDOUT_FILENO);
			close(both_pipe[1][0]);
			close(both_pipe[1][1]);
		}
		if ((state == 2 || state == 3) && fd.in == NULL)
		{
			dup2(both_pipe[0][0], STDIN_FILENO);
			close(both_pipe[0][1]);
			close(both_pipe[0][0]);
		}
		if (fd.int_in != -1)
			dup2(fd.int_in, fd.in->expr.redir.fildes);
		if (fd.int_out != -1)
			dup2(fd.int_out, fd.out->expr.redir.fildes);
		if (is_builtin(all_var[0]))
			exit(start_builtin(all_var, ms));
		else
			execve(path, all_var, ms->env);
	}
	if (state >0)
	{
		if (state != 1)
		{
			close(both_pipe[0][1]);
			close(both_pipe[0][0]);
		}
	}
	if (fd.in != NULL)
		close(fd.int_in);
	if (fd.out != NULL)
		close(fd.int_out);
	return (child);
}
