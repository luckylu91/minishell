/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 23:46:20 by lzins             #+#    #+#             */
/*   Updated: 2021/04/15 00:13:43 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>

int	cd(char **argv)
{
	int ret;

	ret = 0;
	if (!argv[1])
		ret = chdir("~");
	else if (!argv[2])
		ret = chdir(argv[1]);
	else
	{
		bash_error("cd", "too many arguments"); // bash: cd: ...
		return (1); // needed for $?
	}
	if (ret)
		builtin_error("cd", strerror(errno)); // cd: ...
	return (ret);
}
