/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:57:08 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 17:12:00 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_eof(t_block *block)
{
	return (!block);
}

int	is_eof_lst(t_list *block_lst)
{
	return (is_eof(block_at(block_lst)));
}
