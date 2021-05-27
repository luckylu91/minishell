/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:17:35 by lzins             #+#    #+#             */
/*   Updated: 2021/05/27 14:23:17 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include "libft.h"
# include "hist.h"
# include "minishell.h"
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <string.h>

# define LINE_BUFFER_SIZE 80

typedef struct s_term
{
	struct termios	terminal_original;
	struct termios	terminal_settings;
}	t_term;

t_term	g_term;

typedef enum e_termcaps
{
	COLOR_CAP,
	COLOR_BACK_CAP,
	UNDERLINE_CAP,
	BLINK_CAP,
	MOVE_CAP,
	CLEAR_CAP,
	MODIF_ERASE_CAP,
	MOVE_LEFT,
	MOVE_LEFT_ONE,
	MOVE_RIGHT,
	DELETE_CHAR,
	INSERT_MODE,
	INSERT_EXIT,
	NUMBER_OF_CAPS
}				t_termcaps;

void	terminal_done(void);
void	terminal_signal(int signum);
void	init_termios(void);
void	set_terminal_original(void);
void	set_terminal_minishell(void);

void	init_termcaps(void);
char	**init_termcaps_strings(void);
void	free_termcaps(char **tc);

int		ft_putchar(int c);
void	ft_putstr(char *s);
void	clear_line(char **tc);
void	move_to(char **tc, int i, int j);
void	show_prompt(t_minishell *ms);

void	*bigger_calloc(void *ptr, size_t size, size_t incr);
void	linebuffer_add_insert(int c, t_minishell *ms);
void	set_linebuffer_to(char *str, t_minishell *ms);
void	linebuffer_delete_one(t_minishell *ms);
void	linebuffer_clear(t_minishell *ms);

#endif
