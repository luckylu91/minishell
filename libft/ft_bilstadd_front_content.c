/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstadd_front_content.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:12:15 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 18:05:39 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bilstadd_front_content(t_bilist **alst, void *content)
{
	t_bilist *new_elem;

	if (!alst)
		return (0);
	new_elem = ft_bilstnew(content);
	if (!new_elem)
		return (0);
	ft_bilstadd_front(alst, new_elem);
	return (1);
}
