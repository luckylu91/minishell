/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_and_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:20:20 by lzins             #+#    #+#             */
/*   Updated: 2021/04/06 17:20:37 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_and_move(char *str, char *addition)
{
	while (*addition)
	{
		*str = *addition;
		str++;
		addition++;
	}
	return (str);
}
