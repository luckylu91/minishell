/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:30:38 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 19:57:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	find_var(char *arg, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (arg[j] && env[i][j] && (arg[j] == env[i][j]))
			j++;
		if (arg[j] == '\0' && (env[i][j] == '=' || env[i][j] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	**env_new_alloc(char **env, int old)
{
	int		i;
	int		j;
	int		x;
	char	**new;

	j = 0;
	x = 0;
	i = 0;
	while (((env)[i]) != NULL)
		i++;
	new = wrap_malloc(sizeof(char *) * i);
	while (j < i - 1)
	{
		if (x != old)
		{
			new[j] = ft_strdup((env)[x]);
			j++;
		}
		wrap_free((env)[x]);
		x++;
	}
	wrap_free((env));
	new[j] = NULL;
	return (new);
}

int	not_valid_id(char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(arg[i])) && arg[i] != '_')
		return (1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && !(arg[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int	unset_one(char *arg_one, char ***env)
{
	int	j;

	j = find_var(arg_one, *env);
	if (not_valid_id(arg_one))
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(arg_one, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else
	{
		if (j > 0)
			*env = env_new_alloc(*env, j);
		return (0);
	}
}

int	our_unset(char **arg, char ***env)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (arg[i] != NULL)
	{
		if (unset_one(arg[i], env))
			ret = 1;
		i++;
	}
	return (ret);
}
