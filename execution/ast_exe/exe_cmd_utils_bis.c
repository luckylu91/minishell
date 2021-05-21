#include "execution.h"

void	setup_var_exe(both_fd *fd, state_pipe *sp, int state, int **both_pipe)
{
	sp->state = state;
	sp->both_pipe = both_pipe;
	fd->in = NULL;
	fd->out = NULL;
	fd->int_in = -1;
	fd->int_out = -1;
}

void	close_and_dup(state_pipe sp, both_fd fd)
{
	if (sp.state == 1 && fd.out == NULL)
	{
		dup2(sp.both_pipe[1][1], STDOUT_FILENO);
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
}

void	setup_chemin(all_str *chemin, t_ast *cmd)
{
	chemin.all_path = split_path();
	chemin.all_var = from_list_to_str_tab(cmd->expr.command.text_list);
	chemin.path = search_cmd(chemin.all_path, chemin.all_var[0]);
}

void	closing(state_pipe sp, both_fd fd)
{
	if (sp.state > 0)
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
}
