/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:53:12 by lzins             #+#    #+#             */
/*   Updated: 2021/05/08 15:22:23 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	strccpy(char *dst, char *src, char c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i] && src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

int		wrap_free_error(char *line)
{
	wrap_free(line);
	return (-1);
}
