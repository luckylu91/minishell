/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_getenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:37:24 by lzins             #+#    #+#             */
/*   Updated: 2021/05/06 14:13:57 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern t_minishell	g_global_var;

int	our_getenv(t_block *block, char **res_addr)
{
	char *env_str;

	if (is_dollar(block) && block->str && ft_strcmp(block->str, "?") == 0)
		*res_addr = ft_itoa(g_global_var.exit_code);
	else if (is_dollar(block) && block->str && (ft_isalpha(block->str[0]) || block->str[0] == '_'))
	{
		env_str = getenv(block->str);
		if (env_str)
			*res_addr = ft_strdup(env_str);
		else
			*res_addr = ft_strdup("");
	}
	else if (is_tilde(block))
		*res_addr = our_getcwd();
	else
		*res_addr = NULL;
	return (1);
}