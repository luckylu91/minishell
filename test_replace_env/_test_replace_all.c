#include "to_block.h"
#include "ast_api.h"
#include "execution.h"
#include "minishell.h"

int g_exit_code = 0;

int test_replace_line(char *line, t_minishell *ms)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_ast	*ast_cmdchain;
	int		ret;

	printf("Line : '%s'\n", line);

	to_block(line, &block_lst);
	printf("la");
	print_block_list(block_lst);
	printf("\n####\n");

	block_lst_mov = block_lst;
	parse_cmdchain(&ast_cmdchain, &block_lst_mov);
	print_ast(ast_cmdchain);
	printf("\n####\n");
	destroy_block_lst(&block_lst);

	if (replace_env(ast_cmdchain, ms) == -1)
	{
		printf("replace env returned -1\n");
		return (-1);
	}
	print_ast(ast_cmdchain);
	printf("\n");
	if (remove_spaces_cmdchain(ast_cmdchain) == -1)
	{
		printf("ca chie dans remove space\n");
		return (-1);
	}
	print_ast(ast_cmdchain);
	printf("\n");
	destroy_ast(&ast_cmdchain);
	return (1);
}

int main()
{
	t_minishell *ms;

	ms = ft_calloc(1, sizeof(t_minishell));
	setbuf(stdout, NULL);
	printf("replace_line ret = %d\n", test_replace_line("ls pourqoui \"$a\" \"$PATH\" -pas ~ > ~ ", ms));
	printf("\n");
	printf("%s\n", our_getcwd());
	char *envstr;
	printf("ret = %d: %s\n", our_getenv(create_block(dollar_dquote, "PATH"), &envstr, ms), envstr);
}