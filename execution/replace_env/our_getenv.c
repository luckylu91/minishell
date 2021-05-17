/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_getenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:37:24 by lzins             #+#    #+#             */
/*   Updated: 2021/05/12 18:49:08 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


extern t_minishell g_global_var;


char	*search(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = find_var(str, g_global_var.env);
	if (i < 0)
		return (NULL);
	else
	{
		while (g_global_var.env[i][j] != '=')
			j++;
		return (&g_global_var.env[i][j + 1]);
	}	
}

static void	search_env_else_empty(char *str, char **res_addr)
{
	char	*env_str;

	env_str = search(str);
	if (env_str)
		*res_addr = ft_strdup(env_str);
	else
		*res_addr = ft_strdup("");
}


void	our_getenv(t_block *block, char **res_addr)
{
	char	*env_str;

	if (block->f == dollar_dquote && !block->str[0])
		*res_addr = ft_strdup("$");
	if (is_tilde(block))
		search_env_else_empty("HOME", res_addr);
	else if (is_dollar(block) && ft_strcmp(block->str, "?") == 0)
		*res_addr = ft_itoa(g_global_var.exit_code);
	else if (is_dollar(block) && (ft_isalpha(block->str[0]) || block->str[0] == '_'))
		search_env_else_empty(block->str, res_addr);
	else
		*res_addr = NULL;
}
