#include "minishell.h"

int g_exit_code = 0;

int process_line(char *line)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_ast	*ast_cmdchain;
	int		ret;

	printf("Line : '%s'\n", line);

	to_block(line, &block_lst);
	print_block_list(block_lst);
	printf("\n####\n");

	block_lst_mov = block_lst;
	parse_cmdchain(&ast_cmdchain, &block_lst_mov);
	print_ast(ast_cmdchain);
	printf("\n####\n");
	destroy_block_lst(&block_lst);

	if (replace_env(ast_cmdchain) == -1)
		return (-1);
	print_ast(ast_cmdchain);
	printf("\n");
	if (remove_spaces_cmdchain(ast_cmdchain) == -1)
		return (-1);
	print_ast(ast_cmdchain);
	exe_ast(ast_cmdchain, 0, NULL);
	printf("\n");
	destroy_ast(&ast_cmdchain);
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
		return (ret);
	}
	tc = init_termcaps_strings();
	if (!tc)
		return (-1);
	printf("STDIN's tty name : %s\n", ttyname(STDIN_FILENO));
	tty_fd = open(ttyname(STDIN_FILENO), O_RDWR);
	if (tty_fd < 0)
	{
		printf("Cannot open tty of STDIN (%s)\n", ttyname(STDIN_FILENO));
		return (-1);
	}
	line = NULL;
	i = 0;
	while (1)
	{
		c = 0;
		ret = read(tty_fd, &c, sizeof(int));
		if (ret == -1)
			return (ret);
		if (ft_isprint(c))
		{
			if (i % LINE_BUFFER == 0)
				line = bigger_calloc_line(line, i, 80);
			if (!line)
				return (-1);
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
				ft_putchar_fd('\n', tty_fd);
				process_line(line);
				line = NULL;
				i = 0;
			}
			else
				redirect_special((char*)&c, tty_fd);
			//print_escape_sequence((char*)&c, tty_fd);
		}
	}
	return (0);
}
