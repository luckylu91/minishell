/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:39:09 by lzins             #+#    #+#             */
/*   Updated: 2021/05/20 10:14:12 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_context(t_minishell *ms)
{
	copy_environ(&ms->env);
	ms->termcaps = init_termcaps_strings();
	ms->h = create_hist(".histfile");
	ms->lb = ft_calloc(1, sizeof(t_linebuffer));
}

void	init_all(t_minishell *ms)
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

int main()
{
	int			c;
	t_minishell	*ms;
	int			ret_read;

	ms = ft_calloc(1, sizeof(t_minishell));
	init_all(ms);
	if (!isatty(STDIN_FILENO))
		execute_with_file_input(ms);

	show_prompt(ms);
	while (1)
	{
		c = 0;
		// ret_read = read(ms.fd_in, &c, sizeof(int));
		ret_read = read(STDIN_FILENO, &c, sizeof(int));
		if (ret_read == -1)
			exit_with_code(EXIT_FAILURE, ms);
		// else if (ret_read == 0)
		// 	exit_properly(ms);
		process_char(c, ms);
	}
	exit_properly(ms);
}
