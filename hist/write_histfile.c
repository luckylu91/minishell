/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_histfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:22:23 by lzins             #+#    #+#             */
/*   Updated: 2021/05/05 15:30:13 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"


static void	write_lines(t_hist *h, int fd)
{
	char		*line;
	int			i;
	t_bilist	*blst;

	i = 0;
	if (h->hlines)
	{
		rewind_hist(h);
		blst = h->hlines;
		while (((h->histfile_size < 0) || i < h->histfile_size) && blst)
		{
			line = (char*)blst->content;
			ft_putendl_fd(line, fd);
			blst = blst->next;
			i++;
		}
	}
	if (h->file_lines)
	{
		blst = h->file_lines;
		while (((h->histfile_size < 0) || i < h->histfile_size) && blst)
		{
			line = (char*)blst->content;
			ft_putendl_fd(line, fd);
			blst = blst->next;
			i++;
		}
	}
}

int	write_histfile(t_hist *h)
{
	int		fd;
	char	*line;
	int		i;

	if (!h)
		return (1);
	fd = open_error(h->histfile_name, O_CREAT | O_WRONLY, 0666);
	if (fd == -1)
		return (-1);
	write_lines(h, fd);
	close_error(h->histfile_name, fd);
	return (1);
}
