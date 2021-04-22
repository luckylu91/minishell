#include "to_block.h"
#include "ast_api.h"
#include "execution.h"

int test_replace_line(char *line)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_ast	*ast_cmdchain;
	int		ret;

	printf("Line : '%s'\n", line);

	to_block(line, &block_lst);
	print_block_list(block_lst);
	printf("\n####\n");

	block_lst_mov = block_lst;
	parse_cmdchain(&ast_cmdchain, &block_lst_mov);
	print_ast(ast_cmdchain);
	printf("\n####\n");

	if (replace_env(ast_cmdchain) == -1)
		return (-1);
	print_ast(ast_cmdchain);
	exe_ast(ast_cmdchain, 0, NULL);
	printf("\n");
	return (1);
}

int main()
{

	setbuf(stdout, NULL);
	//test_replace_line("ls $pourqoui -pas > lalali");
	printf("\n\n");
//	test_replace_line("$a | ls $pourqoui -pas > $lalali");

//	test_replace_line("echo merguez > test_merguez.txt |  grep m");
//
//
	//test_replace_line(" ls |  grep M ");
	test_replace_line(" ls |  grep M | less");
}
