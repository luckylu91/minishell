/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_histfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:22:23 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 17:52:27 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"
#include "minishell_types.h"

static void	write_memory_lines(t_hist *h, int fd, int *i)
{
	t_bilist	*blst;
	char		*line;

	rewind_hist(h);
	blst = h->hlines;
	while (((h->histfile_size < 0) || *i < h->histfile_size) && blst)
	{
		line = (char *)blst->content;
		ft_putendl_fd(line, fd);
		blst = blst->next;
		(*i)++;
	}
}

static void	write_file_lines(t_hist *h, int fd, int *i)
{
	t_bilist	*blst;
	char		*line;

	blst = h->file_lines;
	while (((h->histfile_size < 0) || *i < h->histfile_size) && blst)
	{
		line = (char *)blst->content;
		ft_putendl_fd(line, fd);
		blst = blst->next;
		(*i)++;
	}
}

static void	write_lines(t_hist *h, int fd)
{
	int	i;

	i = 0;
	if (h->hlines)
		write_memory_lines(h, fd, &i);
	h->file_lines = ft_bilststep(h->file_lines, i);
	if (h->file_lines)
		write_file_lines(h, fd, &i);
}

int	write_histfile(t_hist *h)
{
	int		fd;
	int		flags;

	if (!h || !h->histfile_path)
		return (1);
	flags = O_CREAT | O_WRONLY | O_TRUNC | O_APPEND;
	fd = open_error(h->histfile_path, flags, 0666);
	if (fd == -1)
		return (-1);
	write_lines(h, fd);
	close_error(h->histfile_path, fd);
	return (1);
}
