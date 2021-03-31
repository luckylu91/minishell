#include "block_api.h"

int	is_space(t_block *block)
{
	return (block && block->f == space);
}

int	is_space_lst(t_list *block_lst)
{
	return (is_space(block_at(block_lst)));
}