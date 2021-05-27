/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termios.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:15:46 by lzins             #+#    #+#             */
/*   Updated: 2021/05/27 14:17:29 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	terminal_done(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_term.terminal_original);
}

void	terminal_signal(int signum)
{
	(void)signum;
	if (STDOUT_FILENO != -1)
		tcsetattr(STDOUT_FILENO, TCSANOW, &g_term.terminal_original);
	exit(0);
}

void	set_terminal_original(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_term.terminal_original);
}

void	set_terminal_minishell(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_term.terminal_settings);
}

void	init_termios(void)
{
	if (tcgetattr(STDOUT_FILENO, &g_term.terminal_original)
		|| tcgetattr(STDOUT_FILENO, &g_term.terminal_settings))
	{
		ft_putstr_fd("Cannot initialize terminal: ", STDERR_FILENO);
		ft_putstr_fd(strerror(ENOTSUP), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	g_term.terminal_settings.c_iflag &= ~ISTRIP;
	g_term.terminal_settings.c_iflag &= ~(INLCR | IGNCR);
	g_term.terminal_settings.c_cflag &= ~CSIZE;
	g_term.terminal_settings.c_cflag |= CS8;
	g_term.terminal_settings.c_cflag |= CREAD;
	g_term.terminal_settings.c_lflag |= ISIG;
	g_term.terminal_settings.c_lflag &= ~ICANON;
	g_term.terminal_settings.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
	g_term.terminal_settings.c_lflag &= ~IEXTEN;
	g_term.terminal_settings.c_cc[VTIME] = 0;
	g_term.terminal_settings.c_cc[VMIN] = 1;
	tcsetattr(STDOUT_FILENO, TCSANOW, &g_term.terminal_settings);
}
