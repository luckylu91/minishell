#include "block_api.h"

// ONLY ONE DIGIT ALLOWED
static char	*skip_digit(char *str)
{
	if (ft_isdigit(*str))
		str++;
	return (str);
}

static int redirop_default_fd(char *str)
{
	if (str[0] == '<')
		return (0);
	else
		return (1);
}

void	parse_redirop(t_block *redirop, int *fd, char **symbol_begin)
{
	*symbol_begin = skip_digit(redirop->str);
	if (ft_isdigit(redirop->str[0]))
		*fd = redirop->str[0] - '0';
	else
		*fd = redirop_default_fd(redirop->str);
}
