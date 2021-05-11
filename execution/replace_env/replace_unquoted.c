/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_unquoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:51:13 by lzins             #+#    #+#             */
/*   Updated: 2021/05/08 15:18:40 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Empty env var generates empty list
int	replace_unquoted(t_block *env_block, t_list **replacement)
{
	char	*env_str;
	char	**splitted;
	int		i;
	int		ret;

	*replacement= NULL;
	ret = our_getenv(env_block, &env_str);
	if (ret == -1 || !env_str)
		return (ret);
	splitted = ft_split(env_str, " ");
	wrap_free(env_str);
	if (!splitted)
		return (-1);
	i = -1;
	while (splitted[++i])
	{
		addback_none_block_nodup(replacement, splitted[i]);
		if (splitted[i + 1])
			addback_space_block(replacement);
	}
	wrap_free(splitted);
	return (ret);
}
