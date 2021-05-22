/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:48:38 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 18:45:38 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <limits.h>

static int	ft_isnumber(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	return (*str && ft_all_in(str, "0123456789"));
}

static void	setup(long *res, int *sgn, long *lmt, long *lmr)
{
	*res = 0;
	*sgn = 1;
	*lmt = LONG_MAX / 10;
	*lmr = LONG_MAX % 10;
}

static int	ft_atol_overflows(char *str)
{
	long	res;
	int		sgn;
	long	long_max_tenth;
	long	long_max_rem;

	setup(&res, &sgn, &long_max_tenth, &long_max_rem);
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sgn = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (res > long_max_tenth
			|| (res == long_max_tenth && sgn == 1 && *str - '0' > long_max_rem)
			|| (res == long_max_tenth && sgn == -1 && *str - '0'
				> long_max_rem + 1))
			return (1);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (0);
}

static long	ft_atol(char *str)
{
	unsigned long	res;
	int				sgn;

	res = 0;
	sgn = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sgn = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + sgn * (*str - '0');
		str++;
	}
	return (res);
}

int	our_exit(char **argv, t_minishell *ms)
{
	if (!argv[1])
		ms->exit_code = 0;
	else if (!ft_isnumber(argv[1]) || ft_atol_overflows(argv[1]))
	{
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ms->exit_code = 255;
	}
	else if (argv[2])
	{
		error_message("bash: exit: too many arguments");
		ms->exit_code = 1;
		return (1);
	}
	else
		ms->exit_code = ft_atol(argv[1]) % (long)256;
	ft_exit();
	return (0);
}
