/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:57:39 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 17:12:24 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_wildcard(t_block *block)
{
	return (block && is_special(block) && ft_strcmp(block->str, "*") == 0);
}

int	is_wildcard_lst(t_list *block_lst)
{
	return (is_wildcard(block_at(block_lst)));
}
