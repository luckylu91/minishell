/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:26:22 by lzins             #+#    #+#             */
/*   Updated: 2021/05/25 15:48:02 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_list	*new_list(t_list *block_lst, t_list **redir_blocks,
	t_minishell *ms)
{
	t_list	*new_value;
	t_list	*tail;

	if (!block_lst)
		return (NULL);
	tail = new_list(block_lst->next, redir_blocks, ms);
	if (is_dollar_lst(block_lst) || is_tilde_lst(block_lst))
		new_value = replace_env_block(block_lst, redir_blocks, ms);
	else
	{
		new_value = block_lst;
		new_value->next = NULL;
	}
	if (new_value)
	{
		ft_lstlast(new_value)->next = tail;
		return (new_value);
	}
	else
		return (tail);
}

void	replace_env_list(t_list **block_lst, t_list **redir_blocks,
	t_minishell *ms)
{
	*block_lst = new_list(*block_lst, redir_blocks, ms);
}
