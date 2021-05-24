/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 23:46:20 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 16:57:30 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int update_oldpwd(char ***env)
{
	char	*cwd;
	char	*export_str;

	cwd = our_getcwd();
	if (!cwd)
		return (-1);
	export_str = ft_strjoin("OLDPWD=", cwd);
	export_one(export_str, env);
	wrap_free(cwd);
	wrap_free(export_str);
	return (0);
}

static int update_pwd(char ***env)
{
	char	*cwd;
	char	*export_str;

	cwd = our_getcwd();
	if (!cwd)
		return (-1);
	export_str = ft_strjoin("PWD=", cwd);
	export_one(export_str, env);
	wrap_free(cwd);
	wrap_free(export_str);
	return (0);
}

int	our_chdir(char *path, char ***env)
{
	int	ret;

	update_oldpwd(env);
	ret = chdir(path);
	if (ret)
	{
		bash_error_errno("cd");
		return (1);
	}
	update_pwd(env);
	return (0);
}

int	our_cd(char **argv, char ***env)
{
	int		ret;
	char	*home_dir;

	ret = 0;
	if (!argv[1])
	{
		home_dir = search_env("HOME", *env);
		if (home_dir)
			ret = our_chdir(home_dir, env);
	}
	else
		ret = our_chdir(argv[1], env);
	return (ret);
}
