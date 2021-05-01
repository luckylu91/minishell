/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigger_calloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:01 by lzins             #+#    #+#             */
/*   Updated: 2021/05/01 10:36:59 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	*bigger_calloc(void *ptr, size_t size, size_t incr)
{
	void *ptr_new;

	ptr_new = ft_calloc(1, size + incr);
	if (!ptr)
		return (ptr_new);
	// if (ptr_new)
	// {
		ft_memcpy(ptr_new, ptr, size);
		ft_bzero(ptr_new + size, incr);
	// }
	wrap_free(ptr);
	return (ptr_new);
}
