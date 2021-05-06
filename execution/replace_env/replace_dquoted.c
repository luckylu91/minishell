/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:53:46 by lzins             #+#    #+#             */
/*   Updated: 2021/05/06 14:08:08 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Empty env var generates one non block with empty string
int	replace_dquoted(t_block *env_block, t_list **replacement)
{
	char	*env_str;
	t_block	*new_block;
	int		ret;

	*replacement= NULL;
	ret = our_getenv(env_block, &env_str);
	if (ret == -1)
		return (-1);
	if (!env_str)
		new_block = create_block(none, "");
	else
		new_block = create_block(none, env_str);
	free(env_str);
	if (!new_block)
		return (-1);
	ft_lstadd_back_content(replacement, new_block);
	// printf("(replace_dquoted) *replacement = ");
	// print_block_list(*replacement);
	// printf("\n");
	return (1);
}
