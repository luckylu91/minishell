/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addback_space_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:20:08 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 16:05:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_add.h"

void	addback_space_block(t_list **alst)
{
	t_block	*new_block;

	new_block = ft_calloc(1, sizeof(t_block));
	new_block->f = space;
	new_block->str = NULL;
	ft_lstadd_back_content(alst, new_block);
}
