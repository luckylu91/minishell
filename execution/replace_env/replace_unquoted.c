/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_unquoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:51:13 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 11:20:49 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
		ret = addback_none_block_nodup(replacement, splitted[i]);
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
