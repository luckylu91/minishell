#include "block_api.h"

void destroy_block(void *block_ptr)
{
	t_block *block;

	block = (t_block*)block_ptr;
	if (!block)
		return ;
	// printf("free '%s'\t", block->str);
	free(block->str);
	// printf("free block\n");
	free(block);
}

void	destroy_block_lst(t_list **block_lst)
{
	ft_lstclear(block_lst, destroy_block);
}
