/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:06:31 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 17:30:58 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_tilde(t_block *block)
{
	return (block && block->f == tilde);
}

int	is_tilde_lst(t_list *block_lst)
{
	return (is_tilde(block_at(block_lst)));
}
