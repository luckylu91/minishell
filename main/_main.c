#include "minishell.h"

int g_exit_code = 0;

int exit_properly(int ret, t_hist *h)
{
	terminal_done();
	write_histfile(h);
	exit (ret);
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

int main()
{
	int ret;
	char **tc;
	int	c;
	int	tty_fd;
	struct termios term_attr;
	char *line;
	int i;
	t_hist *h;

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

	printf("STDIN's tty name : %s\n", ttyname(STDIN_FILENO));
	tty_fd = open(ttyname(STDIN_FILENO), O_RDWR);
	if (tty_fd < 0)
	{
		printf("Cannot open tty of STDIN (%s)\n", ttyname(STDIN_FILENO));
		exit_properly(-1, h);
	}
	line = NULL;
	i = 0;
	while (1)
	{
//		printf("la\n");
		c = 0;
		ret = read(tty_fd, &c, sizeof(int));
		if (ret == -1)
			exit_properly(-1, h);
		if (ft_isprint(c))
		{
			if (i % LINE_BUFFER == 0)
				line = bigger_calloc_line(line, i, 80);
			if (!line)
				exit_properly(-1, h);
			line[i] = c;
			i++;
			ft_putchar_fd((char)c, tty_fd);
		}
		else if (c == '\x7f' && i > 0)
		{
			tputs(tparm(tc[MOVE_LEFT], 1), 1, ft_putchar);
			tputs(tc[DELETE_CHAR], 1, ft_putchar);
			// tputs(tc[DELETE_CHAR], 1, ft_putchar);
			line[--i] = '\0';
		}
		else
		{
			if (c == '\n')
			{
//			printf("avant process line\n");
				ft_putchar_fd('\n', tty_fd);
				process_line(line, h);
				// ft_putendl_fd("exe fini\n", tty_fd);
				line = NULL;
				i = 0;
			}
			else
				redirect_special((char*)&c, tty_fd, h, tc, &line, &i);
			//print_escape_sequence((char*)&c, tty_fd);
		}
	}
	exit_properly(0, h);
}
