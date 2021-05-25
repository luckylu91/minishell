/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_block.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:24:22 by lzins             #+#    #+#             */
/*   Updated: 2021/05/25 15:49:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Empty env var generates empty list
static void	replace_unquoted(t_block *env_block, t_list **replacement,
	t_minishell *ms)
{
	char	*env_str;
	char	**splitted;
	int		i;

	*replacement = NULL;
	our_getenv(env_block, &env_str, ms);
	if (!env_str)
		return ;
	splitted = ft_split(env_str, " ");
	wrap_free(env_str);
	i = -1;
	while (splitted[++i])
	{
		addback_none_block_nodup(replacement, splitted[i]);
		if (splitted[i + 1])
			addback_space_block(replacement);
	}
	wrap_free(splitted);
	return ;
}

static void	replace_dquoted(t_block *env_block, t_list **replacement,
	t_minishell *ms)
{
	char	*env_str;
	t_block	*new_block;

	*replacement = NULL;
	our_getenv(env_block, &env_str, ms);
	if (!env_str)
		new_block = create_block(none, "");
	else
		new_block = create_block(none, env_str);
	wrap_free(env_str);
	ft_lstadd_back_content(replacement, new_block);
}

t_list	*replace_env_block(t_list *block_lst, t_list **redir_blocks,
	t_minishell *ms)
{
	t_block	*env_block;
	t_list	*replacement;

	replacement = NULL;
	env_block = block_at(block_lst);
	if (env_block->f == dollar)
		replace_unquoted(env_block, &replacement, ms);
	else if (env_block->f == dollar_dquote || is_tilde(env_block))
		replace_dquoted(env_block, &replacement, ms);
	else if (env_block->f != dollar && env_block->f != dollar_dquote
		&& !is_tilde(env_block))
		replacement = NULL;
	else
		replacement = ft_lstnew(dup_block(block_at(block_lst)));
	if (redir_blocks)
	{
		block_lst->next = NULL;
		ft_lstadd_back(redir_blocks, block_lst);
	}
	else
		ft_lstdelone(block_lst, destroy_block);
	return (replacement);
}
