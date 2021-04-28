/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:21:45 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 18:23:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bilstclear(t_bilist **blst, void (*del)(void*))
{
	t_bilist	*blst_mov1;
	t_bilist	*blst_mov2;

	if (blst == NULL)
		return ;
	blst_mov1 = *blst;
	while (blst_mov1 != NULL)
	{
		blst_mov2 = blst_mov1->next;
		ft_bilstdelone(blst_mov1, del);
		blst_mov1 = blst_mov2;
	}
	*blst = NULL;
}
