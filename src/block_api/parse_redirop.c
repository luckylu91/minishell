/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:57:43 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 17:31:13 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

static char	*skip_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (str);
}

static int	redirop_default_fd(char *str)
{
	if (str[0] == '<')
		return (0);
	else
		return (1);
}

int	parse_redirop_fd(char *str)
{
	int	n;

	n = 0;
	while (ft_isdigit(*str))
	{
		n = 10 * n + *str - '0';
		if (n >= 256)
			return (-1);
		str++;
	}
	return (n);
}

void	parse_redirop(t_block *redirop, int *fd, char **symbol_begin)
{
	*symbol_begin = skip_digit(redirop->str);
	if (ft_isdigit(redirop->str[0]))
		*fd = parse_redirop_fd(redirop->str);
	else
		*fd = redirop_default_fd(redirop->str);
}
