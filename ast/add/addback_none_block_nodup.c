/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addback_none_block_nodup.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:20:06 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 16:05:41 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_add.h"

void	addback_none_block_nodup(t_list **alst, char *str)
{
	t_block	*new_block;

	new_block = ft_calloc(1, sizeof(t_block));
	new_block->f = none;
	new_block->str = str;
	ft_lstadd_back_content(alst, new_block);
}
