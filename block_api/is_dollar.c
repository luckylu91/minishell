/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:33:11 by lzins             #+#    #+#             */
/*   Updated: 2021/04/19 14:36:22 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_dollar(t_block *block)
{
	return (block && (block->f == dollar || block->f == dollar_dquote
			|| block->f == dollar_num));
}

int	is_dollar_lst(t_list *block_lst)
{
	return (is_dollar(block_at(block_lst)));
}
