#include "block_api.h"

int	is_semicol(t_block *block)
{
	return (block && is_special(block) && ft_strcmp(block->str, ";") == 0);
}