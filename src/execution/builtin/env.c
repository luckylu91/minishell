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

int	our_env(char **tab_env)
{
	int	i;

	i = 0;
	while (tab_env[i] != NULL)
	{
		printf("%s\n", tab_env[i]);
		i++;
	}
	return (1);
}