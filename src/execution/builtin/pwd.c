/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:57:55 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 16:38:29 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	our_pwd(char **argv)
{
	char	*working_dir;

	(void)argv;
	working_dir = getcwd(NULL, 0);
	if (!working_dir)
	{
		error_message_errno("pwd", strerror(errno));
		return (-1);
	}
	ft_putendl_fd(working_dir, STDOUT_FILENO);
	free(working_dir);
	return (0);
}