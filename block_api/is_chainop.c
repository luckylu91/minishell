#include "block_api.h"

static int is_chainop_str(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

int	is_chainop(t_block *block)
{
	return (block && is_special(block) && is_chainop_str(block->str));
}

int	is_chainop_lst(t_list *block_lst)
{
	return (is_chainop(block_at(block_lst)));
}