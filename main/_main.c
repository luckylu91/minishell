#include "minishell.h"

extern t_minishell	g_global_var;

void	init_context(void)
{
	ft_bzero(&g_global_var, sizeof(t_minishell));
	copy_environ(&g_global_var.env);
	g_global_var.termcaps = init_termcaps_strings();
	g_global_var.h = create_hist(".histfile");
	g_global_var.lb = ft_calloc(1, sizeof(t_linebuffer));
}

void	signal_interrupt(int signum)
{
	linebuffer_clear();
	rewind_hist(g_global_var.h);
	ft_putchar_fd('\n', g_global_var.fd_out);
	show_prompt();
}

int main()
{
	int ret;
	// char **tc;
	int	c;
	int	tty_fd;
	int	fd_in;
	int	fd_out;
	// t_linebuffer *lb;
	char *line;
	int len_screen;
	t_linebuffer	*lb;
	char			**tc;

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

	init_context();
	ft_get_set_exit_fun(before_exit);
	ft_get_set_context(&g_global_var);

	printf("STDIN's tty name : %s\n", ttyname(STDIN_FILENO));
	tty_fd = open(ttyname(STDIN_FILENO), O_RDWR);
	if (tty_fd < 0)
	{
		printf("Cannot open tty of STDIN (%s)\n", ttyname(STDIN_FILENO));
		g_global_var.fd_in = STDIN_FILENO;
		g_global_var.fd_out = STDOUT_FILENO;
	}
	else
	{
		g_global_var.fd_in = tty_fd;
		g_global_var.fd_out = tty_fd;
	}

	lb = g_global_var.lb;
	tc = g_global_var.termcaps;
	fd_in = g_global_var.fd_in;
	fd_out = g_global_var.fd_out;

	show_prompt();
	while (1)
	{
		c = 0;
		if (read(fd_in, &c, sizeof(int)) == -1)
			exit_with_code(EXIT_FAILURE);
		// printf("i = %d\ni_max = %d\nc = %c\n", lb->i, lb->i_max, (char)c);
		if (ft_isprint(c))
		{
			linebuffer_add_insert(c);
			tputs(tc[INSERT_MODE], 1, ft_putchar);
			ft_putchar_fd((char)c, fd_out);
			tputs(tc[INSERT_EXIT], 1, ft_putchar);
		}
		else if (c == '\x7f' && lb->i_max > 0)
		{
			tputs(tc[MOVE_LEFT_ONE], 1, ft_putchar);
			tputs(tc[DELETE_CHAR], 1, ft_putchar);
			linebuffer_delete_one();
		}
		else
		{
			if (c == '\n' || c == '\0')
			{
				ft_putchar_fd('\n', fd_out);
				process_line(lb->buffer);
				if (c == '\0')
					exit_properly(&g_global_var);
				linebuffer_clear();
				show_prompt();
			}
			else if (is_up_down_arrow(c))
				redirect_up_down((char*)&c);
			else if (is_left_right_arrow(c))
				redirect_left_right((char*)&c);
		}
	}
	exit_properly(&g_global_var);
}
