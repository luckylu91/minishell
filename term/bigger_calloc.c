/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigger_calloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:01 by lzins             #+#    #+#             */
/*   Updated: 2021/05/05 18:56:47 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	*bigger_calloc(void *ptr, size_t size, size_t incr)
{
	void *ptr_new;

	ptr_new = ft_calloc(size + incr, sizeof(char));
	if (!ptr)
		return (ptr_new);
	// if (ptr_new)
	// {
	ft_memcpy(ptr_new, ptr, size);
	// }
	// wrap_free(ptr);
	return (ptr_new);
}
