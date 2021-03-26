#include "block_api.h"

int	is_special(t_block *block)
{
	return (block && block->f == spe);
}

int	is_special_lst(t_list *block_lst)
{
	return (is_special(block_at(block_lst)));
}
