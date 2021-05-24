/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_getenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:37:24 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 18:45:49 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*search_env(char *str, char **env)
{
	int	i;
	int	j;

	j = 0;
	i = find_var(str, env);
	if (i < 0)
		return (NULL);
	else
	{
		while (env[i][j] != '=')
			j++;
		return (&env[i][j + 1]);
	}	
}

void	search_env_else_empty(char *str, char **res_addr, t_minishell *ms)
{
	char	*env_str;

	env_str = search_env(str, ms->env);
	if (env_str)
		*res_addr = ft_strdup(env_str);
	else
		*res_addr = ft_strdup("");
}

void	replace_tilde(char *str, char **res_addr, t_minishell *ms)
{
	char	*home_str;
	char	*res_mov;

	home_str = search_env("HOME", ms->env);
	if (!str[1])
	{
		*res_addr = ft_strdup(home_str);
		return ;
	}
	*res_addr = ft_calloc(ft_strlen(home_str) + ft_strlen(str + 1) + 1,
			sizeof(char));
	res_mov = ft_strcat_and_move(*res_addr, home_str);
	ft_strcat(res_mov, str + 1);
}

void	our_getenv(t_block *block, char **res_addr, t_minishell *ms)
{
	if (block->f == dollar_dquote && !block->str[0])
		*res_addr = ft_strdup("$");
	if (is_tilde(block))
		replace_tilde(block->str, res_addr, ms);
	else if (is_dollar(block) && ft_strcmp(block->str, "?") == 0)
		*res_addr = ft_itoa(ms->exit_code);
	else if (is_dollar(block)
		&& (ft_isalpha(block->str[0]) || block->str[0] == '_'))
		search_env_else_empty(block->str, res_addr, ms);
	else
		*res_addr = NULL;
}
