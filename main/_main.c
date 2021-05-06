#include "minishell.h"

int g_exit_code = 0;

void	exit_properly(void *ms_ptr)
{
	t_minishell *ms;

	ms = ms_ptr;
	terminal_done();
	if (ms)
	{
		if (write_histfile(ms->h) == -1)
			ms->exit_code = -1;
		exit(ms->exit_code);
	}
	else
		exit(0);
}

void	exit_with_code(t_minishell *ms, int code)
{
	ms->exit_code = code;
	exit_properly(ms);
}

int process_line(char *line, t_minishell *ms)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_ast	*ast_cmdchain;
	int		ret;

	if (line && line[0])
		add_hist_line(ms->h, line);
	to_block(line, &block_lst);
	block_lst_mov = block_lst;
	parse_cmdchain(&ast_cmdchain, &block_lst_mov);
	destroy_block_lst(&block_lst);
	if (replace_env(ast_cmdchain) == -1)
		exit_properly(ms);
	if (remove_spaces_cmdchain(ast_cmdchain) == -1)
		return (-1);
	exe_ast(ast_cmdchain, 0, NULL);
	destroy_ast(&ast_cmdchain);
	return (1);
}

int main()
{
	int ret;
	char **tc;
	int	c;
	int	tty_fd;
	int	fd_in;
	int	fd_out;
	t_linebuffer *lb;
	char *line;
	int len_screen;
	t_minishell *ms;

	ms = ft_calloc(1, sizeof(t_minishell));
	if (init_termios() == -1)
	{
		ft_putstr_fd("Cannot initialize terminal: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_exit();
		return (EXIT_FAILURE);
	}
	ft_get_set_exit_fun(exit_properly);
	ft_get_set_context(ms);
	if (init_termcaps() != 1)
	{
		ft_putendl_fd("Error during Termcaps initililisation.", STDERR_FILENO);
		exit_with_code(ms, EXIT_FAILURE);
	}
	tc = init_termcaps_strings();
	ms->h = create_hist(".histfile");
	lb = ft_calloc(1, sizeof(t_linebuffer));

	printf("STDIN's tty name : %s\n", ttyname(STDIN_FILENO));
	tty_fd = open(ttyname(STDIN_FILENO), O_RDWR);
	if (tty_fd < 0)
	{
		printf("Cannot open tty of STDIN (%s)\n", ttyname(STDIN_FILENO));
		fd_in = STDIN_FILENO;
		fd_out = STDOUT_FILENO;
	}
	else
	{
		fd_in = tty_fd;
		fd_out = tty_fd;
	}
	while (1)
	{
		c = 0;
		if (read(fd_in, &c, sizeof(int)) == -1)
			exit_with_code(ms, EXIT_FAILURE);
		// printf("i = %d\ni_max = %d\nc = %c\n", lb->i, lb->i_max, (char)c);
		if (ft_isprint(c))
		{
			linebuffer_add_insert(lb, c);
			tputs(tc[INSERT_MODE], 1, ft_putchar);
			ft_putchar_fd((char)c, fd_out);
			tputs(tc[INSERT_EXIT], 1, ft_putchar);
		}
		else if (c == '\x7f' && lb->i_max > 0)
		{
			tputs(tc[MOVE_LEFT_ONE], 1, ft_putchar);
			tputs(tc[DELETE_CHAR], 1, ft_putchar);
			linebuffer_delete(lb);
		}
		else
		{
			if (c == '\n' || c == '\0')
			{
				ft_putchar_fd('\n', fd_out);
				printf("%s\n", lb->buffer);
				process_line(lb->buffer, ms);
				if (c == '\0')
					exit_properly(ms);
				linebuffer_clear(lb);
			}
			else if (is_up_down_arrow(c))
				redirect_up_down((char*)&c, ms->h, lb, tc, fd_out);
			else if (is_left_right_arrow(c))
				redirect_left_right((char*)&c, lb, tc);
		}
	}
	exit_properly(ms);
}
