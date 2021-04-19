/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_unquoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:51:13 by lzins             #+#    #+#             */
/*   Updated: 2021/04/19 12:21:17 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	addback_none_block(t_list **alst, char *str)
{
	t_block	*new_block;

	new_block = ft_calloc(1, sizeof(t_block));
	if (!new_block)
		return (-1);
	new_block->f = none;
	new_block->str = str;
	return (ft_lstadd_back_content(alst, new_block));
}

static int	addback_space_block(t_list **alst)
{
	t_block	*new_block;

	new_block = ft_calloc(1, sizeof(t_block));
	if (!new_block)
		return (-1);
	new_block->f = space;
	new_block->str = NULL;
	return (ft_lstadd_back_content(alst, new_block));
}

int	replace_unquoted(t_block *env_block, t_list **replacement)
{
	char	*env_str;
	char	**splitted;
	int		i;
	int		ret;

	*replacement= NULL;
	env_str = getenv(env_block->str);
	if (!env_str)
		return (1);
	splitted = ft_split(env_str, " ");
	if (!splitted)
		return (-1);
	i = -1;
	while (splitted[++i])
	{
		ret = addback_none_block(replacement, splitted[i]);
		if (ret >= 0 && splitted[i + 1] && addback_space_block(replacement) < 0)
			ret = -1;
		if (ret < 0)
		{
			ft_splitclear((void **)splitted, i);
			ft_lstclear(replacement, destroy_block);
		}
	}
	free(splitted);
	return (1);
}
