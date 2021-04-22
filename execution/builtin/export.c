/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:02:22 by lzins             #+#    #+#             */
/*   Updated: 2021/04/22 11:36:58 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// [_a-zA-Z][_0-9a-zA-Z]*
int	valid_identifier(char *arg)
{
	int i;

	if (!*arg || *arg == '=')
		return (0);
	if (!ft_isalpha(*arg) && *arg != '_')
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (0);
		i++;
	}
	return (i + 1);
}

static int	not_valid_identifier_error(char *arg)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (-1);
}



static int	enlarge_environ(int new_size, char***our_env)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(new_size, sizeof(char *));
	if (!new_env)
		return (-1);
	i = -1;
	while ((*our_env)[++i])
		new_env[i] = (*our_env)[i];
	free(*our_env);
	*our_env = new_env;
	return (1);
}

static int	export_one(char *arg, char ***our_env)
{
	int			i;
	int			n;

	n = valid_identifier(arg);
	if (!n)
		return (not_valid_identifier_error(arg));
	// TODO do something to export if arg exists already
	if (!arg[n])
		return (1);
	i = -1;
	while ((*our_env)[++i])
	{
		if (ft_strncmp(arg, (*our_env)[i], n) == 0)
			break ;
	}
	if ((*our_env)[i])
		free((*our_env)[i]);
	else if (enlarge_environ(i + 2, our_env) == -1)
		return (-1);
	(*our_env)[i] = ft_strdup(arg);
	if (!(*our_env)[i])
		return (-1);
	return (1);
}

int	export(char **argv, char ***our_env)
{
	int			i;
	int			ret;

	ret = 0;
	i = -1;
	while (argv[++i])
	{
		if (export_one(argv[i], our_env) == -1)
			ret = 1;
	}
	return (ret);
}
