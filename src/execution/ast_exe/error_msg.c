#include "execution.h"

int	exception(char *str)
{
	if (contains_slash(str) && is_dir(NULL, str))
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
