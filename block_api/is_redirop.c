#include "block_api.h"

// ONLY ONE DIGIT ALLOWED
static char	*skip_digit(char *str)
{
	if (ft_isdigit(*str))
		str++;
	return (str);
}

static int is_redirop_str(char *str)
{
	str = skip_digit(str);
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (1);
	if (ft_strcmp(str, "<") == 0)
		return (1);
	if (ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

int	is_redirop(t_block *block)
{
	(block && is_special(block) && is_redirop_str(block->str));
}

int	is_redirop_lst(t_list *block_lst)
{
	return (is_redirop(block_at(block_lst)));
}
