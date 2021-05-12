#include "to_block.h"
#include "ast_api.h"

void print_status(t_status status)
{
	if (status == STATUS_OK)
		printf("STATUS_OK\n");
	if (status == STATUS_ERROR)
		printf("STATUS_ERROR\n");
}

int main()
{
	char *lines[10] = 
	{
		"echo a",
		"echo a ;",
		"echo a ;;",
		"echo a ; ; echo b",
		"; echo a",
		" ;echo a",
		NULL
	};
	t_list	*block_lst;
	t_list	*ast_lst;
	int		i;
	int		ret;

	setbuf(stdout, NULL);

	i = 0;
	while (lines[i])
	{
		printf("Line : \n\t%s\n", lines[i]);
		to_block(lines[i], &block_lst);
		print_block_list(block_lst);
		printf("\n");

		ret = parse_cmdseq(&ast_lst, block_lst);
		printf("ret = ");
		print_status(ret);
		// print_ast_list(ast_lst);

		destroy_block_lst(&block_lst);
		destroy_ast_list(&ast_lst);
		printf("\n");
		i++;
	}
}
