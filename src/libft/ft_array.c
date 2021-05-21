/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:40:21 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 11:41:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_array(size_t size1, size_t size2, size_t type_size)
{
	size_t	i;
	void	**grid;

	grid = ft_calloc(size1, sizeof(void *));
	i = 0;
	while (i < size1)
	{
		grid[i] = ft_calloc(size2, type_size);
		i++;
	}
	return (grid);
}
