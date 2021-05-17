/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:21:30 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 15:04:46 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//	Insert "insertion" between *lst_prev and *lst, then *lst_prev becomes
//	the true predecessor of lst
// void insert_in_list(t_list **lst_prev, t_list *lst, t_list *insert,
// 		t_list **begin)
// {
// 	t_list	*insert_last;

// 	if (!insert)
// 	{
// 		if (begin)
// 			*begin = lst;
// 		if (*lst_prev)
// 			(*lst_prev)->next = lst;
// 		return ;
// 	}
// 	if (begin)
// 	{
// 		// printf("(insert_in_list) *begin = ");
// 		// print_block_list(*begin);
// 		// printf("\n");
// 		*begin = insert;
// 	}
// 	if (*lst_prev)
// 		(*lst_prev)->next = insert;
// 	insert_last = ft_lstlast(insert);
// 	insert_last->next = lst;
// 	*lst_prev = insert_last;
// }


t_list	*replace_env_block(t_list *block_lst, t_list **redir_blocks, t_minishell *ms)
{
	t_block	*env_block;
	t_list	*replacement;

	replacement = NULL;
	env_block = block_at(block_lst);
	if (env_block->f == dollar)
		replace_unquoted(env_block, &replacement, ms);
	else if (env_block->f == dollar_dquote || is_tilde(env_block))
		replace_dquoted(env_block, &replacement, ms);
	else if (env_block->f != dollar && env_block->f != dollar_dquote && !is_tilde(env_block))
		replacement = NULL;
	else
		replacement = ft_lstnew(dup_block(block_at(block_lst)));
	if (redir_blocks)
	{
		block_lst->next = NULL;
		ft_lstadd_back(redir_blocks, block_lst);
	}
	else
		ft_lstdelone(block_lst, destroy_block);
	return (replacement);
}

/*	Replace and destroy the dolar blck at *block_lst
*	Then moves *block_lst to after the replacement (i.e. old block_lst's "next")
*	And block_lst_prev to replacement's last value
*/
// static int	replace_env_block(t_list **lst_prev, t_list *lst, t_list **begin,
// 		t_list **redir_blocks)
// {
// 	t_block	*env_block;
// 	t_list	*replacement;
// 	t_list	*lst_old;

// 	env_block = block_at(lst);
// 	if (env_block->f == dollar)
// 		replace_unquoted(env_block, &replacement);
// 	if (env_block->f == dollar_dquote || is_tilde(env_block))
// 		replace_dquoted(env_block, &replacement);
// 	if (env_block->f != dollar && env_block->f != dollar_dquote && !is_tilde(env_block))
// 		replacement = NULL;
// 	// printf("(replace_env_blocks) replacement = ");
// 	// print_block_list(replacement);
// 	// printf("\n");
// 	lst_old = lst;
// 	lst = lst->next;
// 	lst_old->next = NULL;
// 	insert_in_list(lst_prev, lst, replacement, begin);
// 	if (redir_blocks)
// 		ft_lstadd_back(redir_blocks, lst_old);
// 	else
// 		ft_lstdelone(lst_old, destroy_block);
// 	return (1);
// }

t_list	*replace_env_text(t_list *block_lst, t_list **redir_blocks, t_minishell *ms)
{
	t_list	*new_value;
	t_list	*tail;

	if (!block_lst)
		return (NULL);
	tail = replace_env_text(block_lst->next, redir_blocks, ms);
	if (is_dollar_lst(block_lst) || is_tilde_lst(block_lst))
		new_value = replace_env_block(block_lst, redir_blocks, ms);
	else
	{
		new_value = block_lst;
		new_value->next = NULL;
	}
	if (new_value)
	{
		ft_lstlast(new_value)->next = tail;
		return (new_value);
	}
	else
		return (tail);
}

// static int	replace_env_text(t_list **text_lst, t_list **redir_blocks)
// {
// 	t_list	*lst;
// 	t_list	*lst_prev;

// 	lst = *text_lst;
// 	lst_prev = NULL;
// 	while (lst)
// 	{
// 		// printf("lst:\n");
// 		// print_list_one(lst);
// 		// print_address(lst);
// 		// printf("lst_prev:\n");
// 		// print_list_one(lst_prev);
// 		// print_address(lst_prev);
// 		if (is_dollar_lst(lst) || is_tilde_lst(lst))
// 		{
// 			if (!lst_prev)
// 			{
// 				// printf("text_lst before : ");
// 				// print_block_list(*text_lst);
// 				// printf("\n");
// 				if (replace_env_block(&lst_prev, lst, text_lst, redir_blocks) < 0)
// 					return (-1);
// 				// printf("text_lst after : ");
// 				// print_block_list(*text_lst);
// 				// printf("\n");
// 			}
// 			else if (replace_env_block(&lst_prev, lst, NULL, redir_blocks) < 0)
// 				return (-1);
// 			if (!lst_prev)
// 				break ;
// 			lst = lst_prev->next;
// 		}
// 		else
// 		{
// 			lst_prev = lst;
// 			lst = lst->next;
// 		}
// 	}
// 	return (1);
// }

static int	invalid_file_name(t_list *file_name)
{
	if (!file_name)
		return (1);
	return (ft_lstany(file_name, NULL, is_space_ptr));
}

static int	replace_env_cmd(t_ast *cmd_ast, t_minishell *ms)
{
	t_list	*redir_list;
	t_ast	*redir_ast;
	t_list	*redir_fname;
	t_list	*redir_blocks;
	int		ret;

	cmd_ast->expr.command.text_list = replace_env_text(cmd_ast->expr.command.text_list, NULL, ms);
	redir_blocks = NULL;
	redir_list = cmd_ast->expr.command.redir_list;
	while (redir_list)
	{
		redir_ast = (t_ast *)redir_list->content;
		redir_ast->expr.redir.file_name = replace_env_text(redir_ast->expr.redir.file_name, &redir_blocks, ms);
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

int	replace_env(t_ast *cmdchain_ast, t_minishell *ms)
{
	if (!cmdchain_ast)
		return (1);
	if (cmdchain_ast->type == command_expr)
	{
		if (replace_env_cmd(cmdchain_ast, ms) < 0)
			return (-1);
	}
	else if (cmdchain_ast->type == binary_expr)
	{
		if (replace_env(cmdchain_ast->expr.binary.left, ms) < 0)
			return (-1);
		if (replace_env(cmdchain_ast->expr.binary.right, ms) < 0)
			return (-1);
	}
	return (1);
}
