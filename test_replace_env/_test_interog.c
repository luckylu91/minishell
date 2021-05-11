#include "to_block.h"
#include "ast_api.h"


int main()
{
	t_list *toks = NULL;
	setbuf(stdout, NULL);

	to_block("$?", &toks);
	print_block_list(toks);

	to_block("$123", &toks);
	print_block_list(toks);
}