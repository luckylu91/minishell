/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_unquoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:51:13 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 17:22:25 by lzins            ###   ########lyon.fr   */
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
	free(env_str);
	if (!splitted)
		return (-1);
	i = -1;
	ret = 1;
	while (ret == 1 && splitted[++i])
	{
		ret = addback_none_block_nodup(replacement, splitted[i]);
		if (ret == 1 && splitted[i + 1] && addback_space_block(replacement) < 0)
			ret = -1;
		if (ret == -1)
		{
			ft_splitclear(splitted, i);
			ft_lstclear(replacement, destroy_block);
			break ;
		}
	}
	free(splitted);
	return (ret);
}
