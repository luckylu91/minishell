/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:27:24 by lzins             #+#    #+#             */
/*   Updated: 2021/05/25 18:04:48 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	invalid_file_name(t_list *file_name)
{
	if (!file_name)
		return (1);
	return (ft_lstany(file_name, NULL, is_space_ptr));
}

char	*block_raw_str(t_block *block)
{
	char	*res;
	int		size;
	int		i;

	size = ft_strlen(block->str);
	if (is_dollar(block))
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	i = 0;
	if (is_dollar(block))
		res[i++] = '$';
	ft_strcat(res + 1, block->str);
	return (res);
}

static char	*blocks_to_str(t_list *blocks)
{
	char	*res;
	t_list	*blocks_str_list;

	blocks_str_list = ft_lstmap(blocks, (t_dup_fun)block_raw_str,
			destroy_block);
	res = ft_lststrjoin(blocks_str_list, "", "", "");
	ft_lstclear(&blocks_str_list, wrap_free);
	return (res);
}

void	replace_env_cmd(t_ast *cmd_ast, t_minishell *ms)
{
	t_list	*redir_list;
	t_ast	*redir_ast;
	t_list	*redir_blocks;
	int		ret;

	replace_env_list(&cmd_ast->expr.command.text_list, NULL, ms);
	redir_blocks = NULL;
	redir_list = cmd_redir_list(cmd_ast);
	while (redir_list)
	{
		redir_ast = (t_ast *)redir_list->content;
		replace_env_list(&redir_ast->expr.redir.file_name, &redir_blocks, ms);
		ret = 1;
		if (invalid_file_name(redir_ast->expr.redir.file_name))
		{
			redir_ast->expr.redir.ambiguous_error = 1;
			redir_ast->expr.redir.name_before_replace = \
				blocks_to_str(redir_blocks);
			redir_list = redir_list->next;
			continue ;
		}
		ft_lstclear(&redir_blocks, destroy_block);
		redir_list = redir_list->next;
	}
}
