/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:08:54 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 16:36:14 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

// int tgetflag(char *id);
// char *tgetstr(char *id, char **area); (set area to NULL)
// int tputs(const char *str, int affcnt, int (*putc)(int));
// char *tparm(char *str, ...); (ex tputs(tparm(color_cap, COLOR), 1, putchar))
// char *tgoto(const char *cap, int col, int row); (ex tputs(tgoto(cm_cap, 5, 5), 1, putchar))

int	init_termcaps(void)
{
	char	*term_type;
	int		ret;
	
	term_type = getenv("TERM");
	if (!term_type)
		return (termcaps_term_not_set_error());
	printf("Using terminal %s\n", term_type);
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		return (termcaps_database_not_accessible());
	else if (ret == 0)
		return (termcaps_database_no_entry(term_type));
	return (1);
}

/* COLOR_CAP:		Color (use tputs and then tparm to specify color)
*  COLOR_BACK_CAP:	Color (use tputs and then tparm to specify color)
*  UNDERLINE_CAP:	Underlined (use tputs)
*  BLINK_CAP:		Blink (use tputs)
*  MOVE_CAP:		Move cursor
*  CLEAR_CAP:		Clear text
*  MODIF_ERASE_CAP:	Cancel modifiers
*/
char	**init_termcaps_strings(void)
{
	char	**tc;
	int		i;

	tc = ft_calloc(NUMBER_OF_CAPS, sizeof(char*));
	if (!tc)
		return (NULL);
	tc[COLOR_CAP] = tgetstr("AF", NULL);
	tc[COLOR_BACK_CAP] = tgetstr("AB", NULL);
	tc[UNDERLINE_CAP] = tgetstr("us", NULL);
	tc[BLINK_CAP] = tgetstr("mb", NULL);
	tc[MOVE_CAP] = tgetstr("cm", NULL);
	tc[CLEAR_CAP] = tgetstr("cl", NULL);
	tc[MOVE_LEFT] = tgetstr("LE", NULL);
	tc[DELETE_CHAR] = tgetstr("dc", NULL);
	tc[MODIF_ERASE_CAP] = tgetstr("me", NULL);
	i = 0;
	while (i < NUMBER_OF_CAPS)
	{
		if (!tc[i])
			printf("one termcap is not present\n");
		i++;
	}
	return (tc);
}
