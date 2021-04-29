/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_special_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:03 by lzins             #+#    #+#             */
/*   Updated: 2021/04/29 15:58:52 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	print_escape_sequence(char *str, int fd)
{
	unsigned i = 0;

	while (i < 4 && str[i])
	{
		if (str[i] == '\x1b')
			ft_putstr_fd("ESC", fd);
		else
			ft_putchar_fd(str[i], fd);
		++i;
	}
}

void	redirect_special(char* str, int fd, t_hist *h, char **tc, char **line, int *i)
{
	char	*histline;

	histline = NULL;
	if (ft_strncmp(str, "\x1b[", 2) == 0 && (str[2] == 'A' || str[2] == 'B'))
	{
		tputs(tc[CLEAR_CAP], fd, ft_putchar);
		printf("Key pressed\n");
		if (str[2] == 'A')
			move_hist(h, 1);
		else
			move_hist(h, -1);
		histline = get_hist_line(h);
		if (histline)
			ft_putstr_fd(histline, fd);
		free(*line);
		line = NULL;
		*i = 0;
		if (histline && histline[0])
		{
			*i = ft_strlen(histline);
			*line = ft_calloc(((*i - 1) / LINE_BUFFER + 1) * LINE_BUFFER, sizeof(char));
			ft_memcpy(*line, histline, *i);
		}
	}
}
