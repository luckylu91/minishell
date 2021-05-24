#include "minishell.h"
static void	pre_while(t_minishell *ms, char *line,
	t_list **block_lst, t_list **ast_cmdseq)
{
	ms->all_child = NULL;
	ms->no_pipe_exit_codes = NULL;
	if (!ms->input_is_file)
		set_terminal_original();
	if (line && line[0])
		add_hist_line(ms->h, line);
	to_block(line, block_lst);
//	print_block_list(*block_lst);
	parse_cmdseq(ast_cmdseq, *block_lst);
	
}

static void	process_children(t_minishell *ms)
{
	int	child_pid;
	int	status;

	while (ms->all_child != NULL)
	{
		child_pid = *(int *)(ms->all_child->content);
		if (child_pid > 0)
		{
			waitpid(child_pid, &status, 0);
			if (!WIFSIGNALED(status))
				ms->exit_code = WEXITSTATUS(status);
		}
		else if (child_pid == 0)
		{
			ms->exit_code = *(int *)ms->no_pipe_exit_codes->content;
			ms->no_pipe_exit_codes = ms->no_pipe_exit_codes->next;
		}
		ms->all_child = ms->all_child->next;
	}
}

int	process_line(char *line, t_minishell *ms)
{
	t_list	*block_lst;
	t_list	*ast_cmdseq;

	pre_while(ms, line, &block_lst, &ast_cmdseq);
	while (ast_cmdseq)
	{
		if (replace_env((t_ast *)ast_cmdseq->content, ms) == -1)
			exit_properly(ms);
		if (remove_spaces_cmdchain((t_ast *)ast_cmdseq->content) == -1)
			return (-1);
		exe_ast((t_ast *)ast_cmdseq->content, 0, NULL, ms);
		process_children(ms);
		ast_cmdseq = ast_cmdseq->next;
	}
	if (!ms->input_is_file)
		set_terminal_minishell();
	destroy_block_lst(&block_lst);
	ft_lstclear(&ast_cmdseq, (t_del_fun)destroy_ast);
	return (1);
}
