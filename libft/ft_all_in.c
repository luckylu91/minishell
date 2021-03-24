/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:48:57 by lzins             #+#    #+#             */
/*   Updated: 2021/02/17 16:57:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_all_in(char *str, char *set)
{
	int i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(set, str[i]))
			return (0);
	}
	return (1);
}
