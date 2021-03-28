/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:31:36 by lzins             #+#    #+#             */
/*   Updated: 2021/03/28 13:36:25 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intindex(const int *array, size_t n, int val)
{
	char *memchr_result;

	memchr_result = ft_memchr(array, val, n);
	if (!memchr_result)
		return (-1);
	return ((int)(memchr_result - array));
}
