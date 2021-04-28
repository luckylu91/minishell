/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:09:30 by lzins             #+#    #+#             */
/*   Updated: 2021/04/27 19:01:30 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

int	open_error(char *fname, int flags)
{
	int fd;

	fd = open(fname, flags);
	if (fd == -1)
	{
		ft_putstr_fd("Cannot open file ", STDERR_FILENO);
		ft_putendl_fd(fname, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

int close_error(char *fname, int fd)
{
	int ret;

	ret = close(fd);
	if (ret == -1)
	{
		ft_putstr_fd("Cannot close file ", STDERR_FILENO);
		ft_putendl_fd(fname, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	return (1);
}

t_hist	*create_hist(int hist_size, int histfile_size, char *histfile_name)
{
	t_hist *h;

	h = ft_calloc(1, sizeof(t_hist));
	if (!h)
		return (NULL);
	h->hist_size = hist_size;
	h->histfile_size = histfile_size;
	h->histfile_name = ft_strdup(histfile_name);
	h->lines = NULL;
	if (!h->histfile_name)
	{
		free(h);
		return (NULL);
	}
	return (h);
}

void	truncate_hist(t_hist *h)
{

}

void write_lines_rev_recurs(t_list *lines, int fd)
{
	char *line;

	if (!lines)
		return;
	write_lines_rev_recurs(lines->next, fd);
	line = (char*)lines->content;
	ft_putendl_fd(line, fd);
}

// ne suffit pas, on ne load pas forcement tout le histfile en memoire, donc on ne peut pas
// juste write h->lines
int	write_hist_file(t_hist *h)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_error(h->histfile_name, O_TRUNC | O_WRONLY);
	if (fd == -1)
		return (-1);
	write_lines_rev_recurs(h->lines, fd);
	close_error(h->histfile_name, fd);
}

int parse_hist_file(t_hist *h)
{
	int		fd;
	char	*line;
	int		i;
	int		ret_gnl;

	fd = open_error(h->histfile_name, O_CREAT | O_RDWR);
	if (fd == -1)
		return (-1);
	i = 0;
	ret_gnl = 1;
	while (ret_gnl == 1)
	{
		ret_gnl = get_next_line(fd, &line);
		if (ret_gnl == -1)
		{
			free(line);
			return (-1);
		}
		if (h->histfile_size >= 0 && i == h->histfile_size)
		{
			free(line);
			break ;
		}
		if (!ft_lstadd_front_content(&h->lines, line))
			return (-1);
		free(line);
		i++;
	}
	if (close_error(h->histfile_name, fd) == -1)
		return (-1);
	if (h->histfile_size >= 0 && i == h->histfile_size && ret_gnl == 1)
		return (write_hist_file(h));
	return (1);
}

int	parse_hist_file(t_hist *h)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_error(h->histfile_name, O_CREAT | O_RDWR);
	if (fd == -1)
		return (-1);
	
}
