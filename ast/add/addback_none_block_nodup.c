/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addback_none_block_nodup.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:20:06 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 16:59:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_add.h"

int	addback_none_block_nodup(t_list **alst, char *str)
{
	t_block	*new_block;

	new_block = ft_calloc(1, sizeof(t_block));
	if (!new_block)
		return (-1);
	new_block->f = none;
	new_block->str = str;
	return (ft_lstadd_back_content(alst, new_block));
}
