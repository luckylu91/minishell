#include "minishell.h"

int g_exit_code = 0;

int exit_properly(int ret, t_hist *h)
{
	terminal_done();
	write_histfile(h);
	exit(ret);
}

int process_line(char *line, t_hist *h)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_ast	*ast_cmdchain;
	int		ret;

	// printf("Line : '%s'\n", line);
	if (line && line[0] && add_hist_line(h, line) == -1)
		return (-1);
	to_block(line, &block_lst);
	//  print_block_list(block_lst);
	// printf("\n####\n");

	block_lst_mov = block_lst;
	parse_cmdchain(&ast_cmdchain, &block_lst_mov);
// print_ast(ast_cmdchain);
	// printf("\n####\n");
	destroy_block_lst(&block_lst);
	//  print_block_list(block_lst_mov);

	if (replace_env(ast_cmdchain) == -1)
		exit_properly(-1, h);
	// print_ast(ast_cmdchain);
	// printf("\n");
	if (remove_spaces_cmdchain(ast_cmdchain) == -1)
		return (-1);
	// print_ast(ast_cmdchain);
	exe_ast(ast_cmdchain, 0, NULL);
	// printf("\n");
	destroy_ast(&ast_cmdchain);
//	printf("fin process_line\n");
	return (1);
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
//			printf("avant process line\n");
				ft_putchar_fd('\n', tty_fd);
				line = current_line(lb, h);
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
