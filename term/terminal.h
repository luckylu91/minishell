/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:17:35 by lzins             #+#    #+#             */
/*   Updated: 2021/05/01 11:00:16 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
#define TERMINAL_H

#include "libft.h"
#include "hist.h"
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h> // open
#include <curses.h>
#include <term.h>
#include <string.h>

#define LINE_BUFFER_SIZE 80

typedef struct	s_term
{
	struct termios terminal_original;
	struct termios terminal_settings;
}	t_term;

t_term	term;

typedef enum	e_termcaps
{
	COLOR_CAP,
	COLOR_BACK_CAP,
	UNDERLINE_CAP,
	BLINK_CAP,
	MOVE_CAP,
	CLEAR_CAP,
	MODIF_ERASE_CAP,
	MOVE_LEFT,
	DELETE_CHAR,
	NUMBER_OF_CAPS
}				t_termcaps;

typedef struct	s_linebuffer
{
	char	*buffer;
	int		i;
	int		size;
}				t_linebuffer;

void	terminal_done(void);
void	terminal_signal(int signum);
int	init_termios(void);

int	termcaps_term_not_set_error(void);
int	termcaps_database_not_accessible(void);
int	termcaps_database_no_entry(char *term_type);

int	init_termcaps(void);
char	**init_termcaps_strings(void);

int	ft_putchar(int c);
void	ft_putstr(char *s);
void	clear_line(char **tc);
void	move_to(char **tc, int i, int j);

int		is_up_down_arrow(int c);
int		redirect_special(char* str, t_hist *h);

void	*bigger_calloc(void *ptr, size_t size, size_t incr);
void	linebuffer_add(t_linebuffer *lb, int c);
void	linebuffer_delete(t_linebuffer *lb);
void	linebuffer_clear(t_linebuffer *lb);

#endif
