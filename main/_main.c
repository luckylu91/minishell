/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:39:09 by lzins             #+#    #+#             */
/*   Updated: 2021/05/19 17:39:10 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_context(t_minishell *ms)
{
	ft_bzero(ms, sizeof(t_minishell));
	copy_environ(&ms->env);
	ms->termcaps = init_termcaps_strings();
	ms->h = create_hist(".histfile");
	ms->lb = ft_calloc(1, sizeof(t_linebuffer));
}

void	signal_interrupt(int signum)
{
	t_minishell *ms;

	ms = ft_get_set_context(NULL);
	linebuffer_clear(ms);
	rewind_hist(ms->h);
	if (signum == SIGQUIT)
		ft_putstr_fd("^\\Quit: 3", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	show_prompt(ms);
	ms->prompted_signal = 1;
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
	int ret;
	int	c;
	t_minishell	ms;
	int	ret_read;

	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, signal_interrupt);

	ret = init_termios();
	if (ret == -1)
	if (init_termios() == -1)
	{
		ft_putstr_fd("Cannot initialize terminal: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_exit();
		return (EXIT_FAILURE);
	}

	// termcaps
	if (init_termcaps() != 1)
	{
		ft_putendl_fd("Error during Termcaps initililisation.", STDERR_FILENO);
		exit_with_code(EXIT_FAILURE, &ms);
	}

	init_context(&ms);
	ft_get_set_exit_fun(&before_exit);
	ft_get_set_context(&ms);

	printf("STDIN's tty name : %s\n", ttyname(STDIN_FILENO));
	
	// if (isatty(STDIN_FILENO))
	// {
	// 	ms.fd_in  = open(ttyname(STDIN_FILENO), O_RDWR);
	// 	if (ms.fd_in < 0)
	// 		ms.fd_in = STDIN_FILENO;
	// }
	// else
	// 	execute_with_file_input(&ms);
	if (!isatty(STDIN_FILENO))
		execute_with_file_input(&ms);
	setbuf(stdout, NULL);
	show_prompt(&ms);
	while (1)
	{
		c = 0;
		// ret_read = read(ms.fd_in, &c, sizeof(int));
		ret_read = read(STDIN_FILENO, &c, sizeof(int));
		if (ret_read == -1)
			exit_with_code(EXIT_FAILURE, &ms);
		else if (ret_read == 0)
			exit_properly(&ms);
		if (ft_isprint(c))
		{
			linebuffer_add_insert(c, &ms);
			tputs(ms.termcaps[INSERT_MODE], 1, ft_putchar);
//			ft_putchar_fd((char)c, ms.fd_out);
			ft_putchar_fd((char)c, STDOUT_FILENO);
			tputs(ms.termcaps[INSERT_EXIT], 1, ft_putchar);
		}
		else if (c == '\x7f')
			linebuffer_delete_one(&ms);
		else if (c == '\x9')
			redirect_tab(&ms);
		else
		{
			if (c == '\n')
			{
//				ft_putchar_fd('\n', ms.fd_out);
				ft_putchar_fd('\n', STDOUT_FILENO);
				process_line(ms.lb->buffer, &ms);
				linebuffer_clear(&ms);
				rewind_hist(ms.h);
				if (!ms.prompted_signal)
					show_prompt(&ms);
				ms.prompted_signal = 0;
			}
			else if (is_up_down_arrow(c))
				redirect_up_down((char*)&c, &ms);
			else if (is_left_right_arrow(c))
				redirect_left_right((char*)&c, &ms);
		}
	}
	exit_properly(&ms);
}
