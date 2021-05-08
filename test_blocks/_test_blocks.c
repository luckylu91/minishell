#include "to_block.h"
#include "ast_api.h"

int main()
{
	t_list *blocks;

	setbuf(stdout, NULL);
	to_block("echo \"m", &blocks);
	print_block_list(blocks);
}