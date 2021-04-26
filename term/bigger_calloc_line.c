/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigger_calloc_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:01 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 11:44:08 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	*bigger_calloc_line(void *ptr, size_t size, size_t incr)
{
	void *ptr_new;

	if (!ptr)
		return (ft_calloc(1, size + incr));
	ptr_new = malloc(size + incr);
	if (ptr_new)
	{
		ft_memcpy(ptr_new, ptr, size);
		ft_bzero(ptr_new + size, incr);
	}
	free(ptr);
	return (ptr_new);
}
