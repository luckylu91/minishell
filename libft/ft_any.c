/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_any.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:15:13 by lzins             #+#    #+#             */
/*   Updated: 2021/03/27 11:31:09 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_any(void *array, size_t len, size_t size, int (*booleval)(void*))
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if ((*booleval)(array))
			return (1);
		array += size;
	}
	return (0);
}
