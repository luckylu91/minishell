/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:30:20 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 20:12:45 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	copy_environ(char ***new_env_addr, char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
		i++;
	*new_env_addr = NULL;
	*new_env_addr = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (environ[++i])
		(*new_env_addr)[i] = ft_strdup(environ[i]);
	unset_one("OLDPWD", new_env_addr);
	export_one("OLDPWD", new_env_addr);
	return (1);
}
