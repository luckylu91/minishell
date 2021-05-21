/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_getcwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:53:36 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 14:32:40 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*our_getcwd(void)
{
	size_t	size;
	size_t	increment;
	char	*buf;
	char	*res;

	increment = 40;
	size = increment;
	res = NULL;
	while (!res)
	{
		buf = ft_calloc(size, sizeof(char));
		res = getcwd(buf, size - 1);
		if (res || errno != ERANGE)
			break ;
		wrap_free(buf);
		size += increment;
	}
	return (res);
}
