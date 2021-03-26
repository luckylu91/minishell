#include "block_api.h"

int	is_pipe(t_block *block)
{
	return (block && block->f == spe && ft_strcmp(block->str, "|") == 0);
}