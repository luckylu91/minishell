#include "execution.h"

int	start_builtin(char **c, t_minishell *ms)
{
	int	r;

	r = -1;
	if (ft_strcmp_icase(c[0], "echo") == 0)
		r = our_echo(c);
	if (ft_strcmp_icase(c[0], "cd") == 0)
		r = our_cd(c, &(ms->env));
	if (ft_strcmp_icase(c[0], "pwd") == 0)
		r = our_pwd(c);
	if (ft_strcmp(c[0], "export") == 0)
		r = export(c, &(ms->env));
	else if (ft_strcmp(c[0], "unset") == 0)
		r = our_unset(c, &(ms->env));
	else if (ft_strcmp_icase(c[0], "env") == 0)
		r = our_env(ms->env);
	else if (ft_strcmp(c[0], "exit") == 0)
	{
		r = our_exit(c, ms);
		if (r == 1)
			ms->stop = 1;
	}
	ft_splitclear(c, 0);
	return (r);
}

int	is_builtin(char *c)
{
	if (ft_strcmp_icase(c, "echo") == 0)
		return (1);
	if (ft_strcmp_icase(c, "pwd") == 0)
		return (1);
	if (ft_strcmp_icase(c, "env") == 0)
		return (1);
	return (0);
}

int	is_builtin_nopipe(char *c)
{
	if (ft_strcmp_icase(c, "cd") == 0)
		return (1);
	if (ft_strcmp(c, "unset") == 0)
		return (1);
	if (ft_strcmp(c, "export") == 0)
		return (1);
	if (ft_strcmp(c, "exit") == 0)
		return (1);
	return (0);
}
