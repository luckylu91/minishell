#include "minishell.h"

extern t_minishell	g_global_var;

int process_line(char *line)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_list	*ast_cmdseq;
	t_ast	*ast_cmdchain;
	t_list	*all_child;
	int status;

	all_child = NULL;
	
	set_terminal_original();
	if (line && line[0])
		add_hist_line(g_global_var.h, line);
	to_block(line, &block_lst);
	parse_cmdseq(&ast_cmdseq, block_lst);	
	while(ast_cmdseq)
	{
	//	printf("\narbre loop\n");
	if (replace_env(((t_ast*)(ast_cmdseq->content))) == -1)
		exit_properly(&g_global_var);
	if (remove_spaces_cmdchain(((t_ast*)(ast_cmdseq->content))) == -1)
		return (-1);
	exe_ast(((t_ast*)(ast_cmdseq->content)), 0, NULL, &all_child);
	while (all_child!= NULL)
	{
		waitpid(*((int*)all_child->content), &status,0);
		g_global_var.exit_code = WEXITSTATUS(status);
		all_child =  all_child->next;
	}
	destroy_ast((t_ast **)&ast_cmdseq->content);
	ast_cmdseq=ast_cmdseq->next;
	}

	set_terminal_minishell();
	destroy_block_lst(&block_lst);
	return (1);
}

int process_line_test(char *line)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_list	*ast_cmdseq;
	t_ast	*ast_cmdchain;
	t_list	*all_child;
	int status;

	all_child = NULL;
	
	copy_environ(&(g_global_var.env));
	to_block(line, &block_lst);
	parse_cmdseq(&ast_cmdseq, block_lst);	
//	print_block_list(block_lst);
	while(ast_cmdseq)
	{
	//	printf("\narbre loop\n");
	if (replace_env(((t_ast*)(ast_cmdseq->content))) == -1)
		exit_properly(&g_global_var);
	if (remove_spaces_cmdchain(((t_ast*)(ast_cmdseq->content))) == -1)
		return (-1);
	exe_ast(((t_ast*)(ast_cmdseq->content)), 0, NULL, &all_child);
	while (all_child!= NULL)
	{
		waitpid(*((int*)all_child->content), &status,0);
		g_global_var.exit_code = WEXITSTATUS(status);
		all_child =  all_child->next;
	}
	destroy_ast((t_ast **)&ast_cmdseq->content);
	ast_cmdseq=ast_cmdseq->next;
	}

	destroy_block_lst(&block_lst);
	return (1);
}

