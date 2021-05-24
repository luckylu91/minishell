#include "execution.h"

void	setup_var_exe(int *fd, t_state_pipe *sp, int state,
	int **both_pipe)
{
	int i;

	i = 0;
	while (i<256)
	{
		fd[i] = -2;
		i++;
	}
	sp->state = state;
	sp->both_pipe = both_pipe;
}

int	setup_redir(t_ast *cmd, int *fd)
{
	if ((get_redir_fd(fd, cmd_redir_list(cmd))) < 0)
		return (-1);
	if (cmd_text_list(cmd) == NULL)
		return (-1);
	return (1);
}

void	setup_chemin(t_all_str *chemin, t_ast *cmd, t_minishell *ms)
{
	char	*path;
	char	**path_split;

	chemin->all_var = from_list_to_str_tab(cmd_text_list(cmd));
	path = search_env("PATH", ms->env);
	if (path)
	{
		path_split = ft_split(path, ":");
		chemin->path = search_cmd(path_split, chemin->all_var[0]);
		ft_splitclear(path_split, 0);
	}
	else
		chemin->path = NULL;
}

void	close_and_dup(t_state_pipe sp, int *fd)
{
	if (sp.state == 1 && fd[1] < 0)
	{
		dup2(sp.both_pipe[1][1], STDOUT_FILENO);
		close(sp.both_pipe[1][0]);
		close(sp.both_pipe[1][1]);
	}
	if (sp.state == 3 && fd[1] < 0)
	{
		dup2(sp.both_pipe[1][1], STDOUT_FILENO);
		close(sp.both_pipe[1][0]);
		close(sp.both_pipe[1][1]);
	}
	if ((sp.state == 2 || sp.state == 3) && fd[0] < 0)
	{
		dup2(sp.both_pipe[0][0], STDIN_FILENO);
		close(sp.both_pipe[0][1]);
		close(sp.both_pipe[0][0]);
	}
}

void	closing(t_state_pipe sp, int *fd)
{
	if (sp.state > 0)
	{
		if (sp.state != 1)
		{
			close(sp.both_pipe[0][1]);
			close(sp.both_pipe[0][0]);
		}
	}
	close_all_fd(fd);
}
