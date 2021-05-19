#include "execution.h"

int	start_builtin(char **c, t_minishell *ms)
{
	if (ft_strcmp(c[0], "echo") == 0)
		return (our_echo(c));
	if (ft_strcmp(c[0], "cd") == 0)
		return (our_cd(c, ms->env));
	if (ft_strcmp(c[0], "pwd") == 0)
		return (our_pwd(c));
	if (ft_strcmp(c[0], "export") == 0)
		return (export(c, &(ms->env)));
	else if (ft_strcmp(c[0], "unset") == 0)
		return (our_unset(c, &(ms->env)));
	else if (ft_strcmp(c[0], "env") == 0)
		return (our_env(ms->env));
	else if (ft_strcmp(c[0], "exit") == 0)
		ft_exit();
	return (-1);
}

int	is_builtin(char *c)
{
	if (ft_strcmp(c, "echo") == 0)
		return (1);
	if (ft_strcmp(c, "pwd") == 0)
		return (1);
	if (ft_strcmp(c, "env") == 0)
		return (1);
	return (0);
}

int	is_builtin_nopipe(char *c)
{
	if (ft_strcmp(c, "cd") == 0)
		return (1);
	if (ft_strcmp(c, "unset") == 0)
		return (1);
	if (ft_strcmp(c, "export") == 0)
		return (1);
	if (ft_strcmp(c, "exit") == 0)
		return (1);
	return (0);
}
