/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstadd_front_content.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:12:15 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 16:29:48 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bilstadd_front_content(t_bilist **alst, void *content)
{
	t_bilist	*new_elem;

	if (!alst)
		return ;
	new_elem = ft_bilstnew(content);
	ft_bilstadd_front(alst, new_elem);
}
