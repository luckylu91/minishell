/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:27:24 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 16:40:25 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	invalid_file_name(t_list *file_name)
{
	if (!file_name)
		return (1);
	return (ft_lstany(file_name, NULL, is_space_ptr));
}

int	replace_env_cmd(t_ast *cmd_ast, t_minishell *ms)
{
	t_list	*redir_list;
	t_ast	*redir_ast;
	t_list	*redir_blocks;
	int		ret;

	replace_env_list(&cmd_ast->expr.command.text_list, NULL, ms);
	redir_blocks = NULL;
	redir_list = cmd_ast->expr.command.redir_list;
	while (redir_list)
	{
		redir_ast = (t_ast *)redir_list->content;
		replace_env_list(&cmd_ast->expr.redir.file_name, &redir_blocks, ms);
		ret = 1;
		if (invalid_file_name(redir_ast->expr.redir.file_name))
		{
			redir_ast->expr.redir.ambiguous_error = 1;
			return (ambiguous_redirect_error(redir_blocks));
		}
		ft_lstclear(&redir_blocks, destroy_block);
		redir_list = redir_list->next;
	}
	return (1);
}
