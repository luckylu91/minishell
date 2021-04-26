/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_getenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:37:24 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 16:59:08 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	our_getenv(char *str, char **res_addr)
{
	if (str && ft_strcmp(str, "?") == 0)
	{
		*res_addr = ft_itoa(g_exit_code);
		if (!*res_addr)
			return (-1);
	}
	else if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		*res_addr = NULL;
	else
	{
		*res_addr = ft_strdup(getenv(str));
		if (!*res_addr)
			return (-1);
	}
	return (1);
}