/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:07:23 by lzins             #+#    #+#             */
/*   Updated: 2021/04/28 19:18:15 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIST_H
#define HIST_H

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

typedef struct	s_hist
{
	int			hist_size; // max size during execution
	int			histfile_size; // max size of hist file (in number of lines)
	char		*histfile_name;
	t_bilist	*file_lines;
	t_bilist	*lines;
	char		*current_line;
	int			len; // taille actuelle de hist::lines (garder <= histsize)
}	t_hist;

int	open_error(char *fname, int flags);
int	close_error(char *fname, int fd);
t_hist	*create_hist(char *histfile_name);
void	destroy_hist(t_hist *h);
int	parse_file(char *fname, t_bilist **lines, int limit);
int	write_histfile(t_hist *h);
int	read_truncate_histfile(t_hist *h);
int	add_hist_line(t_hist *h, char *line);
void	rewind_hist(t_hist *h);
int	move_hist(t_hist *h, int direction);
char	*get_hist_line(t_hist *h);

#endif
