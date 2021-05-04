/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:29:32 by lzins             #+#    #+#             */
/*   Updated: 2021/04/30 10:46:25 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstcpy(t_list *src, t_list **adest, size_t content_size)
{
	void	*new_content;

	if (!adest)
		return (0);
	if (!src)
		return (1);
	*adest = NULL;
	new_content = wrap_malloc(content_size);
	if (!new_content
			|| !(*adest = ft_lstnew(new_content))
			|| !ft_lstcpy(src->next, &(*adest)->next, content_size))
	{
		free(new_content);
		free(*adest);
		return (0);
	}
	ft_memcpy(new_content, src->content, content_size);
	return (1);
}
