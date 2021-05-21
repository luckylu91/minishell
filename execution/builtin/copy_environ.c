/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_todo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:30:20 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:30:20 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	copy_environ(char ***new_env_addr, char **environ)
{
	int	i;

	i = 0;
	while (environ[++i]);
	*new_env_addr = NULL;
	*new_env_addr = ft_calloc(i + 1, sizeof(char *));
	if (!*new_env_addr)
		return (-1);
	i = -1;
	while (environ[++i])
	{
		(*new_env_addr)[i] = ft_strdup(environ[i]);
		if (!(*new_env_addr)[i])
		{
			while (--i >= 0)
				wrap_free((*new_env_addr)[i]);
			wrap_free(*new_env_addr);
			return (-1);
		}
	}
	return (1);
}
