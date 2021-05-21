#include "execution.h"
#include <sys/wait.h>

 //void	signal_interrupt_caca(int signum)
 //{
 //	if (signum == SIGINT)
 //		exit(130);
 //	if (signum == SIGQUIT)
 //		exit(131);
 //	exit(0);
 //}

void	child_exe( state_pipe sp, both_fd fd, all_str chemin, t_minishell *ms){
 // signal(SIGINT, signal_interrupt);
		// signal(SIGQUIT, signal_interrupt);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		if (sp.state == 1 && fd.out == NULL)
		{
			dup2(sp.both_pipe[1][1],STDOUT_FILENO);
			close(sp.both_pipe[1][0]);
			close(sp.both_pipe[1][1]);
		}
		if (sp.state == 3 && fd.out == NULL)
		{
			dup2(sp.both_pipe[1][1], STDOUT_FILENO);
			close(sp.both_pipe[1][0]);
			close(sp.both_pipe[1][1]);
		}
		if ((sp.state == 2 || sp.state == 3) && fd.in == NULL)
		{
			dup2(sp.both_pipe[0][0], STDIN_FILENO);
			close(sp.both_pipe[0][1]);
			close(sp.both_pipe[0][0]);
		}
		if (fd.int_in != -1)
			dup2(fd.int_in, fd.in->expr.redir.fildes);
		if (fd.int_out != -1)
			dup3(fd.int_out, fd.out->expr.redir.fildes);
		printf("ici |%s|\n", chemin.all_var[0]);
		if (is_builtin(chemin.all_var[0]))
			exit(start_builtin(chemin.all_var, ms));
		else
			execve(chemin.path, chemin.all_var, ms->env);
}

void	setup_var_exe(both_fd *fd, state_pipe *sp, int state, int **both_pipe)
{
	sp->state = state;
	sp->both_pipe = both_pipe;
	fd->in = NULL;
	fd->out = NULL;
	fd->int_in = -1;
	fd->int_out = -1;
}

void	cmd_notf(all_str chemin, t_minishell *ms, both_fd fd)
{
		pid_t child;
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
			ft_putstr_fd("bash: ",2);
			ft_putstr_fd(chemin.all_var[0],2);
			ft_putstr_fd(": command not found\n",2);
			exit(0);
		}
}
int	exe_cmd(t_ast *cmd, int **both_pipe, int state, t_minishell *ms)
{
	both_fd fd;
	state_pipe sp;
	pid_t child;
	all_str chemin; 

	setup_var_exe(&fd, &sp, state, both_pipe);
	chemin.all_var = from_list_to_str_tab(cmd->expr.command.text_list); 
	if ((get_redir_fd(&fd, cmd->expr.command.redir_list)) < 0)
		return (-1);

	printf("patate 4\n");
	chemin.all_path = split_path();
	if (cmd->expr.command.text_list == NULL)
		return (-1);

	printf("patate 3\n");
	if (check_redir(&fd))
		return (-1);
	chemin.path = search_cmd(chemin.all_path,chemin.all_var[0]); 
	if (chemin.path == NULL && is_builtin(chemin.all_var[0]) == 0 && is_builtin_nopipe(chemin.all_var[0]) == 0)
	{
		cmd_notf(chemin, ms, fd);
		return (-1);
	}
	printf("patate 1\n");
	if (is_builtin_nopipe(chemin.all_var[0]) && sp.state != 0)
	{	
		if (sp.state >0)
		{
			if (sp.state != 1)
			{
				close(sp.both_pipe[0][1]);
				close(sp.both_pipe[0][0]);
			}
		}	
		return (-1);
	}
	else if (is_builtin_nopipe(chemin.all_var[0]))
	{
		int temp;
		if (fd.int_out != -1)
		{
			temp = dup(fd.out->expr.redir.fildes);
			dup2(fd.int_out, fd.out->expr.redir.fildes);
		}
		ms->exit_code = start_builtin(chemin.all_var, ms);

		return (1);
	}

	printf("patate 22\n");
	child = fork();
	if (child == 0)
		child_exe(sp, fd, chemin, ms);
	if (sp.state >0)
	{
		if (sp.state != 1)
		{
			close(sp.both_pipe[0][1]);
			close(sp.both_pipe[0][0]);
		}
	}
	if (fd.in != NULL)
		close(fd.int_in);
	if (fd.out != NULL)
		close(fd.int_out);
	return (child);
}
