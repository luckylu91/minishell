/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:29:32 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 15:48:35 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *src, size_t content_size)
{
	t_list	*lstcpy;
	void	*new_content;

	if (!src)
		return (NULL);
	lstcpy = NULL;
	new_content = wrap_malloc(content_size);
	lstcpy = ft_lstnew(new_content);
	lstcpy->next = ft_lstcpy(src->next, content_size);
	ft_memcpy(new_content, src->content, content_size);
	return (lstcpy);
}
