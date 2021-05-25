#include "execution.h"

int	exception(char *str)
{
	if (!ft_strcmp("/", str) ||!ft_strcmp("/Users", str) )
		return (126);
	if (!ft_strcmp(".", str))
		return (2);
	if (!ft_strcmp("..", str))
		return (127);
	else
		return(0);
}

void	dir_err(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
}

void	filename_err(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": filename argument required\n.: usage: . filename [arguments]\n", 2);
}

void	not_f_err(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	error_msg_all(char *str, int ex)
{
	if (ex == 127)
		not_f_err(str);
	else if (ex == 126)
		dir_err(str);
	else if (ex == 2)
		filename_err(str);
}

void	msg_redir_error(int *fd, fd_err *err)
{
	if (fd[256] == -3)
	{
		ft_putendl_fd("bash: ",2);
		ft_putendl_fd(ft_itoa((err->descri)),2);
		ft_putendl_fd(": Bad file descriptor ",2);
	}
	else if (fd[256] == -2)
	{
		ft_putendl_fd("bash: ",2);
		ft_putendl_fd(err->ambi,2);
		ft_putendl_fd(": ambigous redirect",2);
	}
	else if (fd[256] == -1)
	{
		ft_putendl_fd("bash: ",2);
		ft_putendl_fd(err->file_name,2);
		ft_putendl_fd(": No such file or directory",2);
	}
}
