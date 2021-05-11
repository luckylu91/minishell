/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupstr_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:05:57 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 13:02:28 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dupstr_back(t_list **alst, char *src)
{
	char *copy;

	copy = ft_strdup(src);
	ft_lstadd_back_content(alst, copy);
}
