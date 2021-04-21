/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addback_space_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:20:08 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 11:21:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_add.h"

int	addback_space_block(t_list **alst)
{
	t_block	*new_block;

	new_block = ft_calloc(1, sizeof(t_block));
	if (!new_block)
		return (-1);
	new_block->f = space;
	new_block->str = NULL;
	return (ft_lstadd_back_content(alst, new_block));
}
