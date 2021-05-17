/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 06:19:53 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 13:56:02 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*s_prev;

	if (c == '\0')
		return (ft_strchr(s, '\0'));
	s_prev = NULL;
	s = ft_strchr(s, c);
	while (s != NULL)
	{
		s_prev = s;
		s++;
		s = ft_strchr(s, c);
	}
	return ((char *)s_prev);
}
