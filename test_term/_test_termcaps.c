#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h> // open
#include <string.h>
#include <errno.h>
#include "termios_ex.h"
#include "libft.h"

typedef enum	e_termcaps
{
	COLOR_CAP,
	COLOR_BACK_CAP,
	UNDERLINE_CAP,
	BLINK_CAP,
	MOVE_CAP,
	CLEAR_CAP,
	MODIF_ERASE_CAP,
	NUMBER_OF_CAPS
}				t_termcaps;

int	ft_putchar(int c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	return (0);
}

void	ft_putstr(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
}

int termcaps_init()
{
	int ret;
	char *term_type = getenv("TERM");

	printf("Using terminal %s\n", term_type);
	if (term_type == NULL)
	{
		fprintf(stderr, "TERM must be set (see 'env').\n");
		return -1;
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		fprintf(stderr, "Could not access to the termcap database..\n");
		return -1;
	}
	else if (ret == 0)
	{
		fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
		return -1;
	}
	return 0;
}

char	**init_termcaps(void)
{
	char	**tc;
	int		i;

	tc = ft_calloc(NUMBER_OF_CAPS, sizeof(char*));
	if (!tc)
		return (NULL);
	tc[COLOR_CAP] = tgetstr("AF", NULL); // Color (use tputs and then tparm to specify color)
	tc[COLOR_BACK_CAP] = tgetstr("AB", NULL); // Color (use tputs and then tparm to specify color)
	tc[UNDERLINE_CAP] = tgetstr("us", NULL); // Underlined (use tputs)
	tc[BLINK_CAP] = tgetstr("mb", NULL); // Blink (use tputs)
	tc[MOVE_CAP] = tgetstr("cm", NULL); // Move cursor
	tc[CLEAR_CAP] = tgetstr("cl", NULL); // Clear text
	tc[MODIF_ERASE_CAP] = tgetstr("me", NULL); // Cancel modifiers
	i = 0;
	while (i < NUMBER_OF_CAPS)
	{
		if (!tc[i])
		{
			ft_arrayclear((void**)tc, NUMBER_OF_CAPS);
			return (NULL);
		}
		i++;
	}
	return (tc);
}

void	clear_line(char **tc)
{
	tputs(tc[CLEAR_CAP], 1, ft_putchar);
}

void	move_to(char **tc, int i, int j)
{
	tputs(tgoto(tc[MOVE_CAP], i, j), 1, ft_putchar);
}

void print_escape_sequence(char *str, int fd)
{
	unsigned i = 0;

	while (i < 4 && str[i])
	{
		if (str[i] == '\x1b')
			ft_putstr_fd("ESC", fd);
		else
			ft_putchar_fd(str[i], fd);
		++i;
	}
}

void redirect_special(char* str, int fd)
{
	if (str[0] == '\x1b' && str[1] == '[')
	{
		if (str[2] == 'A')
			ft_putstr_fd("UP", fd);
		if (str[2] == 'B')
			ft_putstr_fd("DOWN", fd);
		if (str[2] == 'C')
			ft_putstr_fd("RIGHT", fd);
		if (str[2] == 'D')
			ft_putstr_fd("LEFT", fd);
	}
}

void	*bigger_calloc(void *ptr, size_t size, size_t incr)
{
	void *ptr_new;

	if (!ptr)
		return (ft_calloc(1, size + incr));
	ptr_new = malloc(size + incr);
	if (ptr_new)
	{
		ft_memcpy(ptr_new, ptr, size);
		ft_bzero(ptr_new + size, incr);
	}
	free(ptr);
	return (ptr_new);
}

void process_line(char *line)
{
	if (!line)
		return ;
	if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		exit(0);
	}
	free(line);
}

// int tgetflag(char *id);
// char *tgetstr(char *id, char **area); (set area to NULL)
// int tputs(const char *str, int affcnt, int (*putc)(int));
// char *tparm(char *str, ...); (ex tputs(tparm(color_cap, COLOR), 1, putchar))
// char *tgoto(const char *cap, int col, int row); (ex tputs(tgoto(cm_cap, 5, 5), 1, putchar))

#define LINE_BUFFER_SIZE 80

int main()
{
	int ret;
	char **tc;
	int	c;
	int	tty_fd;
	struct termios term_attr;
	char *line;
	int i;

	ret = termcaps_init();
	if (ret != 0)
		return (ret);

	tc = init_termcaps();
	if (!tc)
		return (-1);

	if (terminal_init()) {
		if (errno == ENOTTY)
			fprintf(stderr, "This program requires a terminal.\n");
		else
			fprintf(stderr, "Cannot initialize terminal: %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

	printf("STDIN : %s\n", isatty(STDIN_FILENO) ? "IS TTY" : "ISN'T TTY");
	printf("STDOUT : %s\n", isatty(STDOUT_FILENO) ? "IS TTY" : "ISN'T TTY");
	printf("STDERR : %s\n", isatty(STDERR_FILENO) ? "IS TTY" : "ISN'T TTY");
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
		ret = read(tty_fd, &c, sizeof(int));
		if (ret == -1)
			return (ret);
		if (ft_isprint(c))
		{
			if (i % LINE_BUFFER_SIZE == 0)
				line = bigger_calloc(line, i, 80);
			if (!line)
				return (-1);
			line[i] = c;
			i++;
			ft_putchar_fd((char)c, tty_fd);
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
