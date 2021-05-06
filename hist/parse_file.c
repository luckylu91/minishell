/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:33:20 by lzins             #+#    #+#             */
/*   Updated: 2021/05/05 09:47:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

static int	free_lines_error(t_bilist **lines)
{
	ft_bilstclear(lines, free);
	return (-1);
}

static int	parse_file_fd(int fd, t_bilist **lines, int limit)
{
	char	*line;
	int		ret_gnl;
	int		ret;

	ret_gnl = 1;
	while (limit != 0 && ret_gnl == 1)
	{
		ret_gnl = get_next_line(fd, &line);
		if (ret_gnl == -1)
			return (free_lines_error(lines));
		if ((ret_gnl == 0 && ft_strlen(line) > 0) || ret_gnl == 1)
			ft_bilstadd_back_content(lines, line);
		if (limit > 0)
			limit--;
	}
	return (1);
}

int	parse_file(char *fname, t_bilist **lines, int limit)
{
	int	fd;

	*lines = NULL;
	fd = open(fname, O_RDONLY);
	if (fd == -1 && errno == ENOENT)
		return (1);
	else if (fd == -1)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	parse_file_fd(fd, lines, limit);
	if (close_error(fname, fd) == -1)
		return (-1);
	return (1);
}
