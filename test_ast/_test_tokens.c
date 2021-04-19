#include "to_block.h"
#include "ast_api.h"

int main()
{
	char **line;
	char *lines[10] = 
	{
		// "echo a>b",
		// "echo a >b",
		// "echo a> b",
		"echo a > b | ls pourqoui -pas > lalali ; cat $NOOOOON",
		NULL
	};
	t_list *block_lst;
	t_list *ast_lst;

	setbuf(stdout, NULL);

	line = lines;
	while (*line)
	{
		to_block(*line, &block_lst);
		print_block_list(block_lst);
		printf("\n");

		parse_cmdseq(&ast_lst, block_lst);
		print_ast_list(ast_lst);

		destroy_block_lst(&block_lst);
		// block_lst = NULL;
		destroy_ast_list(&ast_lst);
		printf("\n\n\n");
		line++;
	}
}
