/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:17:35 by lzins             #+#    #+#             */
/*   Updated: 2021/05/11 15:36:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
#define TERMINAL_H

#include "libft.h"
#include "hist.h"
#include "minishell.h"
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
	COLOR_CAP,			// 0
	COLOR_BACK_CAP,
	UNDERLINE_CAP,
	BLINK_CAP,
	MOVE_CAP,
	CLEAR_CAP,			// 5
	MODIF_ERASE_CAP,
	MOVE_LEFT,
	MOVE_LEFT_ONE,
	MOVE_RIGHT,
	// MOVE_RIGHT_ONE,
	// DELETE_MODE,
	DELETE_CHAR,		// 10
	// INSERT_CHAR,
	INSERT_MODE,
	INSERT_EXIT,
	// INSERT_PAD,
	NUMBER_OF_CAPS		// 13
}				t_termcaps;

void	terminal_done(void);
void	terminal_signal(int signum);
int		init_termios(void);
void	set_terminal_original(void);
void	set_terminal_minishell(void);

int		init_termcaps(void);
char	**init_termcaps_strings(void);

int		termcaps_term_not_set_error(void);
int		termcaps_database_not_accessible(void);
int		termcaps_database_no_entry(char *term_type);

int		ft_putchar(int c);
void	ft_putstr(char *s);
void	clear_line(char **tc);
void	move_to(char **tc, int i, int j);
void	show_prompt(void);

void	*bigger_calloc(void *ptr, size_t size, size_t incr);
void	linebuffer_add_insert(int c);
void	set_linebuffer_to(char *str);
void	linebuffer_delete_one(void);
void	linebuffer_clear(void);

#endif
