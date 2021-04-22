/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:05:57 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 11:24:47 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstdup_back(t_list **alst, void *aval, size_t size)
{
	void *aval_copy;

	aval_copy = malloc(size);
	if (!aval_copy)
		return (0);
	ft_memcpy(aval_copy, aval, size);
	if (!ft_lstadd_back_content(alst, aval_copy))
	{
		free(aval_copy);
		return (0);
	}
	return (1);
}
