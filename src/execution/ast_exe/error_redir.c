#include "execution.h"

int	set_error_one(t_list *l, t_fd_err *err)
{
	err->file_name = get_char_from_block((((t_ast *)
					(l->content))->expr.redir.file_name));
	return (-1);
}

int	set_error_two(t_list *l, t_fd_err *err)
{
	err->ambi = (((t_ast *)(l->content))->expr.redir).name_before_replace;
	return (-2);
}

int	set_error_three(t_list *l, t_fd_err *err)
{
	if (redir_fd_at(l->content) == -1)
		err->descri = -1;
	else
		err->descri = redir_fd_at(l->content);
	return (-3);
}

void	msg_redir_error(int *fd, t_fd_err *err)
{
	if (fd[256] == -3)
	{
		if (err->descri == -1)
			ft_putstr_fd(
				"bash: file descriptor out of range: Bad file descriptor\n", 2);
		else
		{	
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(ft_itoa((err->descri)), 2);
			ft_putstr_fd(": Bad file descriptor\n", 2);
		}
	}
	else if (fd[256] == -2)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(err->ambi, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	else if (fd[256] == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(err->file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
