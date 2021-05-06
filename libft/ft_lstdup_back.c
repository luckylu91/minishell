/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:05:57 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 15:51:00 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdup_back(t_list **alst, void *aval, size_t size)
{
	void *aval_copy;

	aval_copy = wrap_malloc(size);
	ft_memcpy(aval_copy, aval, size);
	ft_lstadd_back_content(alst, aval_copy);
}
