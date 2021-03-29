#include "block_api.h"

int	is_wildcard(t_block *block)
{
	return (block && is_special(block) && ft_strcmp(block->str, "*") == 0);
}

int	is_wildcard_lst(t_list *block_lst)
{
	return is_wildcard(block_at(block_lst));
}
