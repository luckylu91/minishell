#include "minishell.h"

int	process_line(char *line, t_minishell *ms)
{
	t_list	*block_lst;
	t_list	*block_lst_mov;
	t_list	*ast_cmdseq;
	t_ast	*ast_cmdchain;
	int		status;

	setbuf(stdout, NULL);
	ms->all_child = NULL;
	set_terminal_original();
	if (line && line[0])
		add_hist_line(ms->h, line);
	to_block(line, &block_lst);
	parse_cmdseq(&ast_cmdseq, block_lst);
	while (ast_cmdseq)
	{
		printf("test11\n");
		if (replace_env((t_ast *)ast_cmdseq->content, ms) == -1)
			exit_properly(&g_global_var);
		printf("test22\n");
		if (remove_spaces_cmdchain((t_ast *)ast_cmdseq->content) == -1)
			return (-1);
		exe_ast((t_ast *)ast_cmdseq->content, 0, NULL, ms);
		while (ms->all_child != NULL)
		{
			waitpid(*((int *)(ms->all_child->content)), &status, 0);
			ms->exit_code = WEXITSTATUS(status);
			ms->all_child = ms->all_child->next;
		}
		printf("test5\n");
		destroy_ast((t_ast **)&ast_cmdseq->content);
		printf("test55\n");
		ast_cmdseq = ast_cmdseq->next;
		printf("test555\n");
	}
	printf("test4\n");
	set_terminal_minishell();
	printf("test1\n");
	destroy_block_lst(&block_lst);
	printf("test2\n");
	ft_lstclear(&ast_cmdseq, (t_del_fun)destroy_ast);
	printf("test3\n");
	return (1);
}

// int	process_line_test(char *line, t_minishell *ms)
// {
// 	t_list	*block_lst;
// 	t_list	*block_lst_mov;
// 	t_list	*ast_cmdseq;
// 	t_ast	*ast_cmdchain;
// 	int status;

// 	(ms->all_child) = NULL;
// 	copy_environ(&(ms->env));
// 	to_block(line, &block_lst);
// 	parse_cmdseq(&ast_cmdseq, block_lst);
// 	while(ast_cmdseq)
// 	{
// 		if (replace_env((t_ast*)(ast_cmdseq->content), ms) == -1)
// 			exit_properly(&g_global_var);
// 		if (remove_spaces_cmdchain(((t_ast*)(ast_cmdseq->content))) == -1)
// 			return (-1);
// 		exe_ast(((t_ast*)(ast_cmdseq->content)), 0, NULL, ms);
// 		while (ms->all_child!= NULL)
// 		{
// 			waitpid(*((int*)(ms->all_child->content)), &status,0);
// 			ms->exit_code = WEXITSTATUS(status);
// 			ms->all_child =  ms->all_child->next;
// 		}
// 		destroy_ast((t_ast **)&ast_cmdseq->content);
// 		ast_cmdseq=ast_cmdseq->next;
// 	}

// 	destroy_block_lst(&block_lst);
// 	return (1);
// }
