/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:21:30 by lzins             #+#    #+#             */
/*   Updated: 2021/04/19 17:51:59 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//	Insert "insertion" between *lst_prev and *lst
static void insert_in_list(t_list **lst_prev, t_list *insertion, t_list **lst)
{
	t_list	*insertion_last;

	if (!insertion)
	{
		(*lst_prev)->next = *lst;
		*lst_prev = *lst;
		if (*lst)
			*lst = (*lst)->next;
		return ;
	}
	insertion_last = ft_lstlast(insertion);
	(*lst_prev)->next = insertion;
	insertion_last->next = *lst;
	*lst_prev = insertion_last;
	if (*lst)
		*lst = (*lst)->next;
}

/*	Replace and destroy the dolar blck at *block_lst
*	Then moves *block_lst to after the replacement (i.e. old block_lst's "next")
*	And block_lst_prev to replacement's last value
*/
static int	replace_env_block(t_list **block_lst_prev, t_list **block_lst)
{
	t_block	*env_block;
	t_list	*replacement;
	t_list	*block_lst_old;

	env_block = block_at(*block_lst);
	if (env_block->f == dollar && replace_unquoted(env_block, &replacement) < 0)
		return (-1);
	else if (env_block->f == dollar_dquote
			&& replace_dquoted(env_block, &replacement) < 0)
		return (-1);
	else
		replacement = NULL;
	block_lst_old = *block_lst;
	*block_lst = (*block_lst)->next;
	insert_in_list(block_lst_prev, replacement, block_lst);
	ft_lstdelone(block_lst_old, destroy_block);
	return (1);
}

static int	split_block_lst(t_list *block_lst, t_list **text_ast_lst)
{
	t_status	status;
	t_ast		*text_ast;

	*text_ast_lst = NULL;
	status = parse_text(&text_ast, &block_lst);
	while (status == STATUS_OK && text_ast)
	{
		if (!ft_lstadd_back_content(text_ast_lst, text_ast))
		{
			destroy_ast(&text_ast);
			return (-1);
		}
		status = parse_text(&text_ast, &block_lst);
	}
	if (status == STATUS_OK)
		return (1);
	else
		return (-1);
}

static int	replace_env_text(t_ast *text_ast, t_list **text_ast_lst)
{
	t_list	*block_lst;
	t_list	*block_lst_prev;

	block_lst = text_ast->expr.text;
	block_lst_prev = NULL;
	while (block_lst)
	{
		if (is_dollar_lst(block_lst))
		{
			if (replace_env_block(block_lst_prev, &block_lst) < 0)
				return (-1);
		}
		else
		{
			block_lst_prev = block_lst;
			block_lst = block_lst->next;
		}
	}
	return (split_block_lst(text_ast->expr.text, text_ast_lst));
}

static int	is_dollar_ptr(void *content)
{
	return (is_dollar((t_block *)content));
}

static int	replace_env_list(t_list	*text_lst)
{
	t_list	*text_lst_prev;
	t_ast	*text;

	text_lst_prev = NULL;
	while (text_lst)
	{
		text = (t_ast *)text_lst->content;
		if (ft_lstany(...)))
	}
}

static int	replace_env_cmd(t_ast *cmd_ast)
{
	t_list	*text_list;
	t_list	*redir_list;

	cmd_ast->expr.command.text_list
}

int	replace_env(t_ast *cmdchain_ast)
{
	if (cmdchain_ast->type == command_expr)
	{
		replace_env_cmd(cmdchain_ast);
	}
}
