#include "minishell.h"

extern t_minishell	g_global_var;

int process_line(char *line)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_ast	*ast_cmdchain;
	int		ret;

	if (line && line[0])
		add_hist_line(g_global_var.h, line);
	to_block(line, &block_lst);
	block_lst_mov = block_lst;
	parse_cmdchain(&ast_cmdchain, &block_lst_mov);
	destroy_block_lst(&block_lst);
	if (replace_env(ast_cmdchain) == -1)
		exit_properly(&g_global_var);
	if (remove_spaces_cmdchain(ast_cmdchain) == -1)
		return (-1);
	set_terminal_original();
	exe_ast(ast_cmdchain, 0, NULL);
	set_terminal_minishell();
	destroy_ast(&ast_cmdchain);
	return (1);
}
int process_line_test(char *line)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_ast	*ast_cmdchain;
	int		ret;

	to_block(line, &block_lst);
	block_lst_mov = block_lst;
	parse_cmdchain(&ast_cmdchain, &block_lst_mov);
	destroy_block_lst(&block_lst);
	if (replace_env(ast_cmdchain) == -1)
		exit_properly(&g_global_var);
	if (remove_spaces_cmdchain(ast_cmdchain) == -1)
		return (-1);
	exe_ast(ast_cmdchain, 0, NULL);
	destroy_ast(&ast_cmdchain);
	return (1);
}
