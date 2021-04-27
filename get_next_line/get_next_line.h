/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:38:13 by lzins             #+#    #+#             */
/*   Updated: 2020/11/26 09:07:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

# define MEMORY_SIZE 4096

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_file
{
	int			fd;
	char		buffer[BUFFER_SIZE];
	size_t		head;
}				t_file;

typedef struct	s_files_data
{
	t_file		storage[MEMORY_SIZE];
	size_t		len;
}				t_files_data;

size_t			strccpy(char *dst, char *src, char c, size_t n);
void			ft_bzero(char *s, size_t n);
size_t			ft_strlen(char *s);
int				free_safe(char *line);
t_file			*file_from_fd(int fd);
int				copy_buffer(t_file *file, char **line);
int				read_one_line(t_file *file, char **line);
int				get_next_line(int fd, char **line);

#endif
