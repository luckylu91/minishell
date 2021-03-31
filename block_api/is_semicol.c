#include "block_api.h"

int	is_semicol(t_block *block)
{
	return (block && is_special(block) && ft_strcmp(block->str, ";") == 0);
}

int	is_semicol_lst(t_list *block_lst)
{
	return (is_semicol(block_at(block_lst)));
}
