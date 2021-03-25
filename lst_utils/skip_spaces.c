#include "to_block.h"

static int is_space_fun(void *block_content)
{
	return (is_space((t_block*)block_content));
}