#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>

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

// typedef struct	s_termcaps
// {
// 	char	*cols_cap;
// 	char	*lines_cap;
// 	char	*color_cap;
// 	char	*underline_cap;
// 	char	*curs_mov_cap;
// 	char	*clear_cap;
// 	char	*modif_erase_cap;
// 	char	*overstrike_cap;
// }				t_termcaps;

int	ft_putchar(int c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	return (0);
}

void	ft_putstr(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
}

int init_term()
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

int main(int argc, char **argv)
{
	int ret = init_term();

	/* On évite les warnings pour variables non utilisées. */
	(void)argc;
	(void)argv;

	if (ret != 0)
		return ret;

	int column_count = tgetnum("co");
	int line_count = tgetnum("li");

	printf("#columns = %d\n", column_count);
	printf("#lines   = %d\n", line_count);

	// int tgetflag(char *id);
	// char *tgetstr(char *id, char **area); (set area to NULL)
	// int tputs(const char *str, int affcnt, int (*putc)(int));
	// char *tparm(char *str, ...); (ex tputs(tparm(color_cap, COLOR), 1, putchar))
	// char *tgoto(const char *cap, int col, int row); (ex tputs(tgoto(cm_cap, 5, 5), 1, putchar))

	char **tc;

	tc = init_termcaps();
	if (!tc)
		return (-1);
	printf("Line 1\n");
	// clear_line(tc);
	// printf("Line 2\n");
	move_to(tc, 0, 0);
	while (1);

	return 0;
}