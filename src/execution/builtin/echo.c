/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:26:49 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 14:00:19 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_n_option(char *s)
{
	if (!s)
		return (0);
	if (ft_strncmp(s, "-n", 2) != 0)
		return (0);
	s += 2;
	if (!ft_all_in(s, "n"))
		return (0);
	return (1);
}

int	our_echo(char **argv)
{
	int	nl;
	int	i;
	int	i_start;

	nl = 1;
	i_start = 1;
	while (is_n_option(argv[i_start]))
	{
		nl = 0;
		i_start++;
	}
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
