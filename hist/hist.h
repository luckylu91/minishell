/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:07:23 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 15:51:28 by lzins            ###   ########lyon.fr   */
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
#include <string.h>

typedef enum	e_hist_state {
	BOTTOM,
	MOVING
}				t_hist_state;

typedef struct		s_hist
{
	int				hist_size; // max size during execution
	int				histfile_size; // max size of hist file (in number of lines)
	char			*histfile_name;
	t_bilist		*file_lines;
	t_bilist		*hlines;
	int				len; // taille actuelle de hist::lines (garder <= histsize)
	t_hist_state	position_state;
}	t_hist;

int		open_error(char *fname, int flags, int auth);
int		close_error(char *fname, int fd);
t_hist	*create_hist(char *histfile_name);
void	destroy_hist(t_hist **h);
int		parse_file(char *fname, t_bilist **hlines, int limit);
int		write_histfile(t_hist *h);
int		read_truncate_histfile(t_hist *h);
void	add_hist_line(t_hist *h, char *line);
void	rewind_hist(t_hist *h);
void	move_hist(t_hist *h, int direction);
char	*get_hist_line(t_hist *h);

#endif
