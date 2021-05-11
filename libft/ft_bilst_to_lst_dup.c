/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilst_to_lst_dup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 12:40:29 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 13:54:11 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_bilst_to_lst_dup(t_bilist *blst, t_dup_fun dup)
{
	t_list	*result;

	result = NULL;
	blst = ft_bilstlast(blst);
	while (blst)
	{
		ft_lstadd_front_content(&result, (*dup)(blst->content));
		blst = blst->prev;
	}
	return (result);
}