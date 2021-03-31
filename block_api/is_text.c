/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_text.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:10:28 by lzins             #+#    #+#             */
/*   Updated: 2021/03/31 11:12:12 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_text(t_block *block)
{
	return (!is_special(block) || is_wildcard(block));
}

int	is_text_lst(t_list *block_lst)
{
	return (is_text(block_at(block_lst)));
}
