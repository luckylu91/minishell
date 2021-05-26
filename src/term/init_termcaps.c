/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:08:54 by lzins             #+#    #+#             */
/*   Updated: 2021/05/26 12:24:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

static int	termcaps_term_not_set_error(void)
{
	ft_putstr_fd("TERM is not set\n", STDERR_FILENO);
	ft_putendl_fd("Error during Termcaps initililisation.", STDERR_FILENO);
	return (-1);
}

static int	termcaps_database_not_accessible(void)
{
	ft_putstr_fd("Could not access to the termcap database\n", STDERR_FILENO);
	ft_putendl_fd("Error during Termcaps initililisation.", STDERR_FILENO);
	return (-1);
}

static int	termcaps_database_no_entry(char *term_type)
{
	ft_putstr_fd("Error in finding entry for ", STDERR_FILENO);
	ft_putstr_fd(term_type, STDERR_FILENO);
	ft_putstr_fd(" in the termcaps database", STDERR_FILENO);
	ft_putendl_fd("Error during Termcaps initililisation.", STDERR_FILENO);
	return (-1);
}

void	init_termcaps(void)
{
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");
	if (!term_type)
		exit(termcaps_term_not_set_error());
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		exit(termcaps_database_not_accessible());
	else if (ret == 0)
		exit(termcaps_database_no_entry(term_type));
}

char	**init_termcaps_strings(void)
{
	char	**tc;
	int		i;

	tc = ft_calloc(NUMBER_OF_CAPS, sizeof(char *));
	tc[COLOR_CAP] = tgetstr("AF", NULL);
	tc[COLOR_BACK_CAP] = tgetstr("AB", NULL);
	tc[UNDERLINE_CAP] = tgetstr("us", NULL);
	tc[BLINK_CAP] = tgetstr("mb", NULL);
	tc[MOVE_CAP] = tgetstr("cm", NULL);
	tc[CLEAR_CAP] = tgetstr("cl", NULL);
	tc[MOVE_LEFT] = tgetstr("LE", NULL);
	tc[MOVE_LEFT_ONE] = tgetstr("le", NULL);
	tc[MOVE_RIGHT] = tgetstr("RI", NULL);
	tc[DELETE_CHAR] = tgetstr("dc", NULL);
	tc[INSERT_MODE] = tgetstr("im", NULL);
	tc[INSERT_EXIT] = tgetstr("ei", NULL);
	tc[MODIF_ERASE_CAP] = tgetstr("me", NULL);
	i = 0;
	while (i < NUMBER_OF_CAPS)
	{
		if (!tc[i])
			printf("One termcap is not present : %d\n", i);
		i++;
	}
	return (tc);
}
