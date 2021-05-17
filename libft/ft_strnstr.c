/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 07:15:14 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 13:57:59 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	compute_i_max(size_t hay_len, size_t needle_len, size_t n)
{
	if (hay_len < n)
		return (hay_len - needle_len);
	else
		return (n - needle_len);
}

char	*ft_strnstr(const char *hay, const char *needle, size_t n)
{
	size_t	needle_len;
	size_t	hay_len;
	size_t	i;
	size_t	i_max;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)hay);
	needle_len = ft_strlen(needle);
	hay_len = ft_strlen(hay);
	if (needle_len > hay_len || needle_len > n)
		return (NULL);
	i_max = compute_i_max(hay_len, needle_len, n);
	i = -1;
	while (++i <= i_max)
	{
		j = 0;
		while (j < needle_len && hay[i + j] == needle[j])
			j++;
		if (j == needle_len)
			return ((char *)hay + i);
	}
	return (NULL);
}
