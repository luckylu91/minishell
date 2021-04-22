/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:10:28 by lzins             #+#    #+#             */
/*   Updated: 2021/04/19 14:36:54 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_text(t_block *block)
{
	return (is_rawtext(block) || is_dollar(block));
}

int	is_text_lst(t_list *block_lst)
{
	return (is_text(block_at(block_lst)));
}
