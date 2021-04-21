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

	ret = replace_env(ast_cmdchain);
	print_ast(ast_cmdchain);
	printf("\n");

	return (ret);
}

int main()
{
	char	*line = "$a | ls $pourqoui -pas > lalali";

	setbuf(stdout, NULL);
	test_replace_line("echo $a | ls $pourqoui -pas > lalali");
	printf("\n\n");
	test_replace_line("$a | ls $pourqoui -pas > $lalali");
}