/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:57:29 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 16:57:30 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_special(t_block *block)
{
	return (block && block->f == spe);
}

int	is_special_lst(t_list *block_lst)
{
	return (is_special(block_at(block_lst)));
}
