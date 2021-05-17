/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_getenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:37:24 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 15:58:16 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*search(char *str, t_minishell *ms)
{
	int	i;
	int	j;

	j = 0;
	i = find_var(str, ms->env);
	if (i < 0)
		return (NULL);
	else
	{
		while (ms->env[i][j] != '=')
			j++;
		return (&ms->env[i][j + 1]);
	}	
}

static void	search_env_else_empty(char *str, char **res_addr, t_minishell *ms)
{
	char	*env_str;

	env_str = search(str, ms);
	if (env_str)
		*res_addr = ft_strdup(env_str);
	else
		*res_addr = ft_strdup("");
}


void	our_getenv(t_block *block, char **res_addr, t_minishell *ms)
{
	char	*env_str;

	if (block->f == dollar_dquote && !block->str[0])
		*res_addr = ft_strdup("$");
	if (is_tilde(block))
		search_env_else_empty("HOME", res_addr, ms);
	else if (is_dollar(block) && ft_strcmp(block->str, "?") == 0)
		*res_addr = ft_itoa(ms->exit_code);
	else if (is_dollar(block) && (ft_isalpha(block->str[0]) || block->str[0] == '_'))
		search_env_else_empty(block->str, res_addr, ms);
	else
		*res_addr = NULL;
}
