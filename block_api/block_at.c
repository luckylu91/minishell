#include "block_api.h"

t_block	*block_at(t_list *blocks)
{
	if (!blocks)
		return (NULL);
	return ((t_block*)(blocks->content));
}