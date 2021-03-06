#include "minishell.h"

static void	pre_while(t_minishell *ms, char *line, t_list **ast_cmdseq)
{
	t_list	*block_lst;

	ms->all_child = NULL;
	ms->no_pipe_exit_codes = NULL;
	if (!ms->input_is_file)
		set_terminal_original();
	if (line && line[0])
		add_hist_line(ms->h, line);
	to_block(line, &block_lst);
	if (parse_cmdseq(ast_cmdseq, block_lst) == STATUS_ERROR)
		ms->exit_code = 258;
	destroy_block_lst(&block_lst);
}

static t_list	*delone_and_take_next(t_list *lst)
{
	t_list	*next;

	next = lst->next;
	ft_lstdelone(lst, wrap_free);
	return (next);
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
		ms->all_child = delone_and_take_next(ms->all_child);
	}
}

int	process_line(char *line, t_minishell *ms)
{
	t_list	*ast_cmdseq;
	t_list	*ast_cmdseq_begin;

	ms->stop = 0;
	setbuf(stdout, NULL);
	pre_while(ms, line, &ast_cmdseq);
	ast_cmdseq_begin = ast_cmdseq;
	while (ast_cmdseq && ms->stop == 0)
	{
		replace_env((t_ast *)ast_cmdseq->content, ms);
		remove_spaces_cmdchain((t_ast *)ast_cmdseq->content);
		exe_ast((t_ast *)ast_cmdseq->content, 0, NULL, ms);
		process_children(ms);
		ast_cmdseq = ast_cmdseq->next;
	}
	ms->stop = 0;
	if (!ms->input_is_file)
		set_terminal_minishell();
	destroy_ast_list(&ast_cmdseq_begin);
	return (0);
}
