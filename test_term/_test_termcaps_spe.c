#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>

#include "libft.h"

int	ft_putchar(int c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	return (0);
}

void	ft_putstr(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
}

void print_escape_sequence(char *str)
{
	unsigned i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\x1b')
			ft_putstr("ESC");
		else
			ft_putchar(str[i]);
		++i;
	}
	ft_putchar('\n');
}

int main(int argc, char **argv)
{
	char buff[2];

	buff[1] = '\0';
	while (1)
	{
		if (read(STDIN_FILENO, &buff, 1) == -1)
		{
			ft_putstr("ERROR\n");
			return (-1);
		}
		print_escape_sequence(buff);
	}
}