/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 23:46:20 by lzins             #+#    #+#             */
/*   Updated: 2021/04/27 14:55:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	our_cd(char **argv)
{
	int ret;

	ret = 0;
	if (!argv[1])
		ret = chdir("~");
	else if (!argv[2])
		ret = chdir(argv[1]);
	else
	{
		error_message("bash: cd: too many arguments"); // bash: cd: ...
		return (1); // needed for $?
	}
	if (ret)
		error_message_errno("cd", strerror(errno)); // cd: ...
	return (ret);
}
