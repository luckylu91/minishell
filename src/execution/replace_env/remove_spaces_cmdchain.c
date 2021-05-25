#include "execution.h"

int	remove_spaces_redir(t_ast *redir_ast)
{
	t_list	*new_fname;

	remove_spaces(redir_ast->expr.redir.file_name, &new_fname);
	ft_lstclear(&redir_ast->expr.redir.file_name, destroy_block);
	redir_ast->expr.redir.file_name = new_fname;
	return (1);
}

void	remove_spaces_cmd(t_ast *cmd_ast)
{
	t_list	*new_text_lst;
	t_list	*redir_lst;

	remove_spaces(cmd_ast->expr.command.text_list, &new_text_lst);
	ft_lstclear(&cmd_ast->expr.command.text_list, destroy_block);
	cmd_ast->expr.command.text_list = new_text_lst;
	redir_lst = cmd_ast->expr.command.redir_list;
	while (redir_lst)
	{
		remove_spaces_redir((t_ast *)redir_lst->content);
		redir_lst = redir_lst->next;
	}
}

int	remove_spaces_cmdchain(t_ast *cmdchain_ast)
{
	if (!cmdchain_ast)
		return (1);
	if (cmdchain_ast->type == command_expr)
		remove_spaces_cmd(cmdchain_ast);
	else if (cmdchain_ast->type == binary_expr)
	{
		remove_spaces_cmdchain(cmdchain_ast->expr.binary.left);
		remove_spaces_cmdchain(cmdchain_ast->expr.binary.right);
	}
	return (0);
}
