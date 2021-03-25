/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:09 by lzins             #+#    #+#             */
/*   Updated: 2021/03/25 14:22:04 by hgallien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "to_block.h"
void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (alst == NULL)
	{	
		printf("penis\n");
		return ;
	}
	else if (*alst == NULL)
	{

		printf("penis2\n");
		*alst = new;
	}
		else
		{

		printf("penis3\n");
		ft_lstlast(*alst)->next = new;
	}
		}
