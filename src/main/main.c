/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:39:09 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 11:26:21 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_context(t_minishell *ms, char **environ)
{
	char	*cwd;

	copy_environ(&ms->env, environ);
	cwd = our_getcwd();
	ms->h = create_hist(ft_strjoin(cwd, "/.histfile"));
	wrap_free(cwd);
	if (!ms->h)
		ft_exit();
	ms->lb = ft_calloc(1, sizeof(t_linebuffer));
}

void	init_all(t_minishell *ms, char **environ)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, signal_interrupt);
	init_context(ms, environ);
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

	(void)argc;
	(void)argv;
	ms = ft_calloc(1, sizeof(t_minishell));
	init_all(ms, environ);
	if (!isatty(STDIN_FILENO))
		execute_with_file_input(ms);
	init_termios();
	init_termcaps();
	ms->termcaps = init_termcaps_strings();
	if (argc >= 2)
	{
		process_line(argv[1], ms);
		exit(0);
	}
	// else
	// 	dprintf(1, "debug de l'argv %d\n", argc);
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
