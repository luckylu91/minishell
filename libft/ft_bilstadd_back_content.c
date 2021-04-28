/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bilstadd_back_content.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:08:05 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 17:09:55 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bilstadd_back_content(t_bilist **alst, void *content)
{
	t_bilist *new_elem;

	if (!alst)
		return (0);
	new_elem = ft_bilstnew(content);
	if (!new_elem)
		return (0);
	ft_bilstadd_back(alst, new_elem);
	return (1);
}
