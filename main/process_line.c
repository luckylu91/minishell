#include "minishell.h"

int process_line(char *line, t_hist *h)
{
	t_list	*block_lst;
	t_list	*ast_cmdseq;
	t_ast	*ast_cmdchain;
	int		ret;

	// printf("Line : '%s'\n", line);
	if (line && line[0] && add_hist_line(h, line) == -1)
		return (-1);
	to_block(line, &block_lst);
	//  print_block_list(block_lst);
	// printf("\n####\n");

	parse_cmdseq(&ast_cmdseq, block_lst);
	while (ast_cmdseq)
	{
		ast_cmdchain = (t_ast *)ast_cmdseq->content;
		// print_ast(ast_cmdchain);
		// printf("\n####\n");
		//	destroy_block_lst(&block_lst);
		//if (block_lst_mov == NULL)
		//	printf("c nul\n");
		//print_block_list(block_lst_mov);
		if (replace_env(ast_cmdchain) == -1)
			exit_properly(-1, h);
		// print_ast(ast_cmdchain);
		// printf("\n");
		if (remove_spaces_cmdchain(ast_cmdchain) == -1)
			return (-1);
		// print_ast(ast_cmdchain);
		exe_ast(ast_cmdchain, 0, NULL);
		// printf("\n");
		ast_cmdseq = ast_cmdseq->next;
		//	printf("fin process_line\n");
	}
	destroy_ast_list(&ast_cmdseq);
	destroy_block_lst(&block_lst);
	return (1);
}
