/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_rawtext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:33:09 by lzins             #+#    #+#             */
/*   Updated: 2021/04/19 14:34:21 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_rawtext(t_block *block)
{
	return (block && block->f == none);
}

int	is_rawtext_lst(t_list *block_lst)
{
	return (is_rawtext(block_at(block_lst)));
}
