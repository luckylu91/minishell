/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:57:26 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 16:57:27 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_space(t_block *block)
{
	return (block && block->f == space);
}

int	is_space_ptr(void *block_ptr)
{
	return (is_space((t_block *)block_ptr));
}

int	is_space_lst(t_list *block_lst)
{
	return (is_space(block_at(block_lst)));
}
