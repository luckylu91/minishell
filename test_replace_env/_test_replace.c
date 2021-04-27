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
	printf("\n");
	exe_ast(ast_cmdchain, 0, NULL);
	printf("exit code = %i\n",ast_cmdchain->exit_code);
	printf("\n");
	return (1);
}

int main()
{

	setbuf(stdout, NULL);
	//test_replace_line("ls $pourqoui -pas > lalali");
//	printf("\n\n");
//	test_replace_line("$a | ls $pourqoui -pas > $lalali");

//	test_replace_line("echo merguez > test_merguez.txt |  grep m");
//
//
//	test_replace_line(" ls |  grep M ");
//	test_replace_line(" ls |  grep M | less");
//	test_replace_line(" echo patate > a > b > c <asdasd >d | ls");
	
//	test_replace_line(" cat Makefile | sort | grep #"); 
	//test_replace_line(" ls |  grep M | grep Z | true");
	//test_replace_line(" ls |  grep M | grep Z ");
	
//	test_replace_line("false | true |false | true") ;
	
	test_replace_line("echo la france");
	//test_replace_line("echo merguez > test_merguez.txt |  grep m < test_merguez.txt");
	//test_replace_line("cat asdasdasdasd");
	//test_replace_line("false");
	
	//test_replace_line("true");
//	test_replace_line("grep m < test_merguez.txt");
}
