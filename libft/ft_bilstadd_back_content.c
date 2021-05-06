/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstadd_back_content.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:08:05 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 16:30:10 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bilstadd_back_content(t_bilist **alst, void *content)
{
	t_bilist *new_elem;

	if (!alst)
		return ;
	new_elem = ft_bilstnew(content);
	ft_bilstadd_back(alst, new_elem);
}
