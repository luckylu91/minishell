/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:03:20 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 16:33:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

int	open_error(char *fname, int flags, int auth)
{
	int	fd;

	fd = open(fname, flags, auth);
	if (fd == -1)
	{
		ft_putstr_fd("Cannot open file ", STDERR_FILENO);
		ft_putendl_fd(fname, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

int	close_error(char *fname, int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
	{
		ft_putstr_fd("Cannot close file ", STDERR_FILENO);
		ft_putendl_fd(fname, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	return (1);
}
