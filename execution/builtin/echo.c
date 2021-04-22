/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:26:49 by lzins             #+#    #+#             */
/*   Updated: 2021/04/16 13:56:13 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	echo(char **argv)
{
	int	nl;
	int	i;
	int	i_start;

	nl = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		nl = 0;
		i_start = 2;
	}
	else
		i_start = 1;
	i = i_start;
	while (argv[i])
	{
		if (i > i_start)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
