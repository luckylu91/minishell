/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 23:46:20 by lzins             #+#    #+#             */
/*   Updated: 2021/05/19 16:26:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	our_cd(char **argv, char **env)
{
	int		ret;
	char	*home_dir;

	ret = 0;
	if (!argv[1])
	{
		home_dir = search_env("HOME", env);
		if (home_dir)
			ret = chdir(home_dir);
	}
	else if (!argv[2])
		ret = chdir(argv[1]);
	else
	{
		error_message("bash: cd: too many arguments");
		return (1);
	}
	if (ret)
	{
		error_message_errno("cd", strerror(errno));
		return (1);
	}
	return (0);
}
