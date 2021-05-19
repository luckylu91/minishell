/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_semicol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:57:22 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 16:57:23 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

int	is_semicol(t_block *block)
{
	return (block && is_special(block) && ft_strcmp(block->str, ";") == 0);
}

int	is_semicol_lst(t_list *block_lst)
{
	return (is_semicol(block_at(block_lst)));
}
