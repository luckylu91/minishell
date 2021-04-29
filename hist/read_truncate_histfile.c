/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_truncate_histfile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:04:55 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 09:29:11 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

// static int	above_limit(t_bilist *lst, int size)
// {
// 	if (size < 0)
// 		return (0);
// 	return (ft_bilstsize(lst) > size);
// }

// static void	truncate_list(t_bilist **alst, int n, void (*del)(void *))
// {
// 	if (n < 0 || !*alst)
// 		return ;
// 	if (n == 0)
// 		ft_bilstclear(alst, del);
// 	truncate_list(&(*alst)->next, n - 1, del);
// }

static int	dup_n_str(t_bilist **dest, t_bilist *src, int n)
{
	void		*new_content;
	t_bilist	*new_elem;

	*dest = NULL;
	if (n <= 0 || !src)
		return (1);
	src = ft_bilststep_blocking(src, n);
	while (n > 0 && src)
	{
		new_content = ft_strdup((char *)src->content);
		if (!ft_bilstadd_front_content(dest, new_content))
		{
			free(new_content);
			ft_bilstclear(dest, free);
			return (-1);
		}
		src = src->prev;
		n--;
	}
	return (1);
}

int	read_truncate_histfile(t_hist *h)
{
	if (parse_file(h->histfile_name, &h->file_lines, h->histfile_size) == -1)
		return (-1);
	if (dup_n_str(&h->lines, h->file_lines, h->hist_size) == -1)
		return (-1);
	return (1);
}
