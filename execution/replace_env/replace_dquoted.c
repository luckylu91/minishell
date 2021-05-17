/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:53:46 by lzins             #+#    #+#             */
/*   Updated: 2021/05/12 18:38:43 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Empty env var generates one non block with empty string
void	replace_dquoted(t_block *env_block, t_list **replacement)
{
	char	*env_str;
	t_block	*new_block;
	int		ret;

	*replacement= NULL;
	our_getenv(env_block, &env_str);
	if (!env_str)
		new_block = create_block(none, "");
	else
		new_block = create_block(none, env_str);
	wrap_free(env_str);
	ft_lstadd_back_content(replacement, new_block);
	// printf("(replace_dquoted) *replacement = ");
	// print_block_list(*replacement);
	// printf("\n");
}
