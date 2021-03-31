#include "block_api.h"

int is_eof(t_block *block)
{
	return (!block);
}

int is_eof_lst(t_list *block_lst)
{
	return (is_eof(block_at(block_lst)));
}
