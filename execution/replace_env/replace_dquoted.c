/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:53:46 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 17:05:12 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Empty env var generates one non block with empty string
int	replace_dquoted(t_block *env_block, t_list **replacement)
{
	char	*env_str;
	t_block	*new_block;

	*replacement= NULL;
	env_str = getenv(env_block->str);
	if (!env_str)
		env_str = "";
	new_block = create_block(none, env_str);
	if (!new_block)
		return (-1);
	if (!ft_lstadd_back_content(replacement, new_block))
	{
		destroy_block(new_block);
		return (-1);
	}
	return (1);
}
