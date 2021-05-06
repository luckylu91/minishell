#include "block_api.h"

void destroy_block(void *block_ptr)
{
	t_block *block;

	block = (t_block*)block_ptr;
	if (!block)
		return ;
	wrap_free(block->str);
	wrap_free(block);
}

void	destroy_block_lst(t_list **block_lst)
{
	ft_lstclear(block_lst, destroy_block);
}
