/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:06:55 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 15:35:04 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_splitclear(char **splitted, int i_start)
{
	int	i;

	i = i_start;
	while (splitted[i])
	{
		wrap_free(splitted[i]);
		i++;
	}
	wrap_free(splitted);
}
