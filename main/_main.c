#include "minishell.h"

int g_exit_code = 0;

t_global_var global_var;
int exit_properly(int ret, t_hist *h)
{
	terminal_done();
	write_histfile(h);
	exit(ret);
}

static char *current_line(t_linebuffer *lb, t_hist *h)
{
	char *histline;

	histline = get_hist_line(h);
	if (!lb->buffer && !histline)
		return (ft_strdup(""));
	if (!lb->buffer)
		return (ft_strdup(histline));
	if (!histline)
		return (ft_strdup(lb->buffer));
	return (ft_strjoin(histline, lb->buffer));
}

int main()
{
	int ret;
	char **tc;
	int	c;
	int	tty_fd;
	struct termios term_attr;
	t_hist *h;
	t_linebuffer *lb;
	char *line;
	int len_screen;

	copy_environ(&global_var.env);
	ret = init_termios();
	if (ret == -1)
	{
		ft_putstr_fd("Cannot initialize terminal: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ret = init_termcaps();
	if (ret != 1)
	{
		ft_putendl_fd("Error during Termcaps initililisation.", STDERR_FILENO);
		exit_properly(ret, h);
	}
	tc = init_termcaps_strings();
	if (!tc)
		exit_properly(-1, h);

	h = create_hist(".histfile");
	lb = ft_calloc(1, sizeof(t_linebuffer));

	printf("STDIN's tty name : %s\n", ttyname(STDIN_FILENO));
	tty_fd = open(ttyname(STDIN_FILENO), O_RDWR);
	if (tty_fd < 0)
	{
		printf("Cannot open tty of STDIN (%s)\n", ttyname(STDIN_FILENO));
		exit_properly(-1, h);
	}
	while (1)
	{
		//		printf("la\n");
		c = 0;
		ret = read(tty_fd, &c, sizeof(int));
		if (ret == -1)
			exit_properly(-1, h);
		if (ft_isprint(c))
		{
			linebuffer_add(lb, c);
			ft_putchar_fd((char)c, tty_fd);
		}
		else if (c == '\x7f' && lb->i > 0)
		{
			tputs(tparm(tc[MOVE_LEFT], 1), 1, ft_putchar);
			tputs(tc[DELETE_CHAR], 1, ft_putchar);
			linebuffer_delete(lb);
		}
		else
		{
			if (c == '\n')
			{
				printf("avant putchard fd\n");
				ft_putchar_fd('\n', tty_fd);

				printf("avant current line\n");
				line = current_line(lb, h);
				printf("avant process line\n");
				printf("process_line : %d\n", process_line(line, h));
				// ft_putendl_fd("exe fini\n", tty_fd);
				linebuffer_clear(lb);
			}
			else if (is_up_down_arrow(c))
			{
				line = current_line(lb, h);
				len_screen = line ? ft_strlen(line) : 0;
				if (redirect_special((char*)&c, h))
				{
					tputs(tparm(tc[MOVE_LEFT], len_screen), 1, ft_putchar);
					for (int k = 0; k < len_screen; k++)
						tputs(tc[DELETE_CHAR], 1, ft_putchar);
					line = current_line(lb, h);
					ft_putstr_fd(line, tty_fd);
				}
			}
			//print_escape_sequence((char*)&c, tty_fd);
		}
	}
	exit_properly(0, h);
}
