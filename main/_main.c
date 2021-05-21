/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:39:09 by lzins             #+#    #+#             */
/*   Updated: 2021/05/20 12:07:21 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_context(t_minishell *ms, char **environ)
{
	copy_environ(&ms->env, environ);
	ms->termcaps = init_termcaps_strings();
	ms->h = create_hist(".histfile");
	ms->lb = ft_calloc(1, sizeof(t_linebuffer));
}

void	init_all(t_minishell *ms, char **environ)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, signal_interrupt);
	init_termios();
	init_termcaps();
	init_context(ms);
	ft_get_set_exit_fun(&before_exit);
	ft_get_set_context(ms);
}

void	execute_with_file_input(t_minishell *ms)
{
	int		ret_gnl;
	char	*line;

	ret_gnl = 1;
	while (ret_gnl == 1)
	{
		ret_gnl = get_next_line(STDIN_FILENO, &line);
		if (ret_gnl == 1)
			process_line(line, ms);
		wrap_free(line);
	}
	if (ret_gnl == -1)
		exit_with_code(EXIT_FAILURE, ms);
	exit_properly(ms);
}

int	main(int argc, char **argv, char **environ)
{
	int			c;
	t_minishell	*ms;
	int			ret_read;

	ms = ft_calloc(1, sizeof(t_minishell));
	init_all(ms, environ);
	if (!isatty(STDIN_FILENO))
		execute_with_file_input(ms);
	show_prompt(ms);
	while (1)
	{
		c = 0;
		ret_read = read(STDIN_FILENO, &c, sizeof(int));
		if (ret_read == -1)
			exit_with_code(EXIT_FAILURE, ms);
		process_char(c, ms);
	}
	exit_properly(ms);
}
