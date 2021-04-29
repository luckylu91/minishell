/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:47:46 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 10:02:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_dup;
	size_t	s_len;

	s_len = ft_strlen(s);
	s_dup = malloc(s_len + 1);
	if (!s_dup)
		return (NULL);
	return (ft_memcpy(s_dup, s, s_len + 1));
}
