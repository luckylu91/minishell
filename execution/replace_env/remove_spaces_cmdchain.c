#include "execution.h"

int	remove_spaces_redir(t_ast *redir_ast)
{
	t_list	*new_fname;
	int	ret;

	ret = remove_spaces(redir_ast->expr.redir.file_name, &new_fname);
	if (ret == -1)
		return (-1);
	ft_lstclear(&redir_ast->expr.redir.file_name, destroy_block);
	redir_ast->expr.redir.file_name = new_fname;
	return (1);
}

int	remove_spaces_cmd(t_ast *cmd_ast)
{
	t_list	*new_text_lst;
	t_list	*redir_lst;
	int		ret;

	ret = remove_spaces(cmd_ast->expr.command.text_list, &new_text_lst);
	if (ret == -1)
		return (-1);
	ft_lstclear(&cmd_ast->expr.command.text_list, destroy_block);
	cmd_ast->expr.command.text_list = new_text_lst;
	redir_lst = cmd_ast->expr.command.redir_list;
	while (redir_lst)
	{
		ret = 1;
		if (remove_spaces_redir((t_ast*)redir_lst->content) == -1)
			return (-1);
		redir_lst = redir_lst->next;
	}
	return (1);
}

int	remove_spaces_cmdchain(t_ast *cmdchain_ast)
{
	if (cmdchain_ast->type == command_expr
			&& remove_spaces_cmd(cmdchain_ast) == -1)
		return (-1);
	else if (cmdchain_ast->type == binary_expr)
	{
		if (remove_spaces_cmdchain(cmdchain_ast->expr.binary.left) == -1)
			return (-1);
		if (remove_spaces_cmdchain(cmdchain_ast->expr.binary.right) == -1)
			return (-1);
	}
	return (1);
}