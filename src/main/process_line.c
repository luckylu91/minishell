#include "minishell.h"

void	pre_while(t_minishell *ms, char *line,
	t_list **block_lst, t_list **ast_cmdseq)
{
	ms->all_child = NULL;
	ms->no_pipe_exit_codes = NULL;
	set_terminal_original();
	if (line && line[0])
		add_hist_line(ms->h, line);
	to_block(line, block_lst);
	parse_cmdseq(ast_cmdseq, *block_lst);
}

int	process_line(char *line, t_minishell *ms)
{
	t_list	*block_lst;
	t_list	*ast_cmdseq;
	int		child_pid;
	int		status;

	pre_while(ms, line, &block_lst, &ast_cmdseq);
	while (ast_cmdseq)
	{
		if (replace_env((t_ast *)ast_cmdseq->content, ms) == -1)
			exit_properly(ms);
		if (remove_spaces_cmdchain((t_ast *)ast_cmdseq->content) == -1)
			return (-1);
		exe_ast((t_ast *)ast_cmdseq->content, 0, NULL, ms);
		// printf("Number of child to wait : %d\n", ft_lstsize(ms->all_child));
		while (ms->all_child != NULL)
		{
			child_pid = *(int *)(ms->all_child->content);
			if (child_pid > 0)
			{
				waitpid(child_pid, &status, 0);
				if (!WIFSIGNALED(status))
					ms->exit_code = WEXITSTATUS(status);
			}
			else
			{
				ms->exit_code = *(int *)ms->no_pipe_exit_codes->content;
				ms->no_pipe_exit_codes = ms->no_pipe_exit_codes->next;
			}
			ms->all_child = ms->all_child->next;
		}
		ast_cmdseq = ast_cmdseq->next;
	}
	set_terminal_minishell();
	destroy_block_lst(&block_lst);
	ft_lstclear(&ast_cmdseq, (t_del_fun)destroy_ast);
	// printf("after process_line ms->exit_code = %d\n", ms->exit_code);
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
