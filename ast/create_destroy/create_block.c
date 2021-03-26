/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:44:24 by lzins             #+#    #+#             */
/*   Updated: 2021/03/26 10:06:29 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "block_api.h"

t_block *create_block(enum flags f, char *str)
{
	t_block *block_new;

	block_new = ft_calloc(1, sizeof(t_block));
	if (!block_new)
		return (NULL);
	block_new->f = f;
	if (str)
	{
		block_new->str = ft_strdup(str);
		if (!block_new->str)
		{
			free(block_new);
			return (NULL);
		}
	}
	return (block_new);
}