/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigger_calloc_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:01 by lzins             #+#    #+#             */
/*   Updated: 2021/04/30 23:33:10 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	*bigger_calloc_line(void *ptr, size_t size, size_t incr)
{
	void *ptr_new;

	if (!ptr)
		return (ft_calloc(1, size + incr));
	ptr_new = wrap_malloc(size + incr);
	if (ptr_new)
	{
		ft_memcpy(ptr_new, ptr, size);
		ft_bzero(ptr_new + size, incr);
	}
	wrap_free(ptr);
	return (ptr_new);
}
