/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:39:12 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 15:31:02 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"
#include "ast_alloc.h"

t_block	*dup_block(t_block *block)
{
	t_block	*block_copy;

	if (!block)
		return (NULL);
	block_copy = ft_calloc(1, sizeof(t_block));
	block_copy->f = block->f;
	if (!block->str)
		return (block_copy);
	block_copy->str = ft_strdup(block->str);
	return (block_copy);
}
