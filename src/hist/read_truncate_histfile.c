/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_truncate_histfile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:04:55 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 17:46:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

static void	dup_n_str(t_bilist **dest, t_bilist *src, int n)
{
	void		*new_content;

	*dest = NULL;
	if (n == 0 || !src)
		return ;
	if (n > 0)
		src = ft_bilststep_blocking(src, n);
	else
		src = ft_bilstlast(src);
	while (n != 0 && src)
	{
		new_content = ft_strdup((char *)src->content);
		ft_bilstadd_front_content(dest, new_content);
		src = src->prev;
		if (n > 0)
			n--;
	}
}

int	read_truncate_histfile(t_hist *h)
{
	if (parse_file(h->histfile_path, &h->file_lines, h->histfile_size) == -1)
		return (-1);
	dup_n_str(&h->hlines, h->file_lines, h->hist_size);
	return (1);
}
