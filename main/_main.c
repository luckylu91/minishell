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
	ft_putchar_fd('\n', ms->fd_out);
	show_prompt(ms);
}

int main()
{
	int ret;
	// char **tc;
	int	c;
	int	tty_fd;
	// int	fd_in;
	// int	fd_out;
	// t_linebuffer *lb;
	char *line;
	int len_screen;
	// t_linebuffer	*lb;
	// char			**tc;
	t_minishell	ms;

	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, terminal_signal);
	signal(SIGTERM, terminal_signal);

	//termios
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
		exit_with_code(EXIT_FAILURE);
	}

	init_context(&ms);
	ft_get_set_exit_fun(before_exit);
	ft_get_set_context(&ms);

	printf("STDIN's tty name : %s\n", ttyname(STDIN_FILENO));
	tty_fd = open(ttyname(STDIN_FILENO), O_RDWR);
	if (tty_fd < 0)
	{
		printf("Cannot open tty of STDIN (%s)\n", ttyname(STDIN_FILENO));
		ms.fd_in = STDIN_FILENO;
		ms.fd_out = STDOUT_FILENO;
	}
	else
	{
		ms.fd_in = tty_fd;
		ms.fd_out = tty_fd;
		// dup2(STDIN_FILENO, tty_fd);
		// dup2(STDOUT_FILENO, tty_fd);
	}

	// lb = g_global_var.lb;
	// tc = g_global_var.termcaps;
	// fd_in = g_global_var.fd_in;
	// fd_out = g_global_var.fd_out;

	//
	setbuf(stdout, NULL);//
	show_prompt(&ms);
	while (1)
	{
		c = 0;
		if (read(ms.fd_in, &c, sizeof(int)) == -1)
			exit_with_code(EXIT_FAILURE);
		// printf("i = %d\ni_max = %d\nc = %c\n", lb->i, lb->i_max, (char)c);
		if (ft_isprint(c))
		{
			linebuffer_add_insert(c, &ms);
			tputs(ms.termcaps[INSERT_MODE], 1, ft_putchar);
			ft_putchar_fd((char)c, ms.fd_out);
			tputs(ms.termcaps[INSERT_EXIT], 1, ft_putchar);
		}
		else if (c == '\x7f')
			linebuffer_delete_one(&ms);
		else if (c == '\x9')
			redirect_tab(&ms);
		else
		{
			if (c == '\n')// || c == '\0')
			{
				ft_putchar_fd('\n', ms.fd_out);
				process_line(ms.lb->buffer, &ms);
				if (c == '\0')
					exit_properly(&ms);
				linebuffer_clear(&ms);
				show_prompt(&ms);
			}
			else if (is_up_down_arrow(c))
				redirect_up_down((char*)&c, &ms);
			else if (is_left_right_arrow(c))
				redirect_left_right((char*)&c, &ms);
		}
	}
	exit_properly(&ms);
}
