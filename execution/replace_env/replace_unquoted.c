/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_unquoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:51:13 by lzins             #+#    #+#             */
/*   Updated: 2021/05/12 18:05:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Empty env var generates empty list
void	replace_unquoted(t_block *env_block, t_list **replacement)
{
	char	*env_str;
	char	**splitted;
	int		i;
	int		ret;

	*replacement= NULL;
	our_getenv(env_block, &env_str);
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
