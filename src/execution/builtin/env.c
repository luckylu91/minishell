/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:30:17 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:31:35 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_equal(char *c)
{
	return (*c == '=');
}

int	contains_equal(char *str)
{
	return (ft_any(str, ft_strlen(str), 1, (t_bool_fun)is_equal));
}

int	our_env(char **tab_env)
{
	int	i;

	i = 0;
	while (tab_env[i] != NULL)
	{
		if (contains_equal(tab_env[i]))
			printf("%s\n", tab_env[i]);
		i++;
	}
	return (0);
}
