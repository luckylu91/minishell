/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:21:30 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 18:13:22 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// void print_list_one(t_list *l)
// {
// 	t_block *content;

// 	if (!l)
// 	{
// 		printf("\t(null)\n");
// 		return ;
// 	}
// 	content = (t_block*)l->content;
// 	printf("\tcontent = ");
// 	print_block(content);
// 	printf(", next = %p\n", l->next);
// }

// void print_address(t_list *l)
// {
// 	printf("\tAddress :\t%p\n", l);
// }

//	Insert "insertion" between *lst_prev and *lst, then *lst_prev becomes
//	the true predecessor of lst
void insert_in_list(t_list **lst_prev, t_list *lst, t_list *insert,
		t_list **begin)
{
	t_list	*insert_last;

	if (!insert)
	{
		if (begin)
			*begin = lst;
		if (*lst_prev)
			(*lst_prev)->next = lst;
		return ;
	}
	if (begin)
		*begin = insert;
	if (*lst_prev)
		(*lst_prev)->next = insert;
	insert_last = ft_lstlast(insert);
	insert_last->next = lst;
	*lst_prev = insert_last;
}

// //	Insert "insertion" between *lst_prev and *lst
// static void insert_in_list(t_list **lst_prev, t_list *insertion, t_list **lst)
// {
// 	t_list	*insertion_last;

// 	if (!insertion)
// 	{
// 		(*lst_prev)->next = *lst;
// 		*lst_prev = *lst;
// 		if (*lst)
// 			*lst = (*lst)->next;
// 		return ;
// 	}
// 	insertion_last = ft_lstlast(insertion);
// 	(*lst_prev)->next = insertion;
// 	insertion_last->next = *lst;
// 	*lst_prev = insertion_last;
// 	if (*lst)
// 		*lst = (*lst)->next;
// }

/*	Replace and destroy the dolar blck at *block_lst
*	Then moves *block_lst to after the replacement (i.e. old block_lst's "next")
*	And block_lst_prev to replacement's last value
*/
static int	replace_env_block(t_list **lst_prev, t_list *lst, t_list **begin,
		t_list **redir_blocks)
{
	t_block	*env_block;
	t_list	*replacement;
	t_list	*lst_old;

	env_block = block_at(lst);
	if (env_block->f == dollar && replace_unquoted(env_block, &replacement) < 0)
		return (-1);
	else if ((env_block->f == dollar_dquote || is_tilde(env_block))
			&& replace_dquoted(env_block, &replacement) < 0)
		return (-1);
	else
		replacement = NULL;
	printf("Block list : ");
	print_block_list(replacement);
	printf("\n");
	lst_old = lst;
	lst = lst->next;
	lst_old->next = NULL;
	insert_in_list(lst_prev, lst, replacement, begin);
	if (redir_blocks)
		ft_lstadd_back(redir_blocks, lst_old);
	else
		ft_lstdelone(lst_old, destroy_block);
	return (1);
}

// /*	Replace and destroy the dolar blck at *block_lst
// *	Then moves *block_lst to after the replacement (i.e. old block_lst's "next")
// *	And block_lst_prev to replacement's last value
// */
// static int	replace_env_block(t_list **block_lst_prev, t_list **block_lst)
// {
// 	t_block	*env_block;
// 	t_list	*replacement;
// 	t_list	*block_lst_old;

// 	env_block = block_at(*block_lst);
// 	if (env_block->f == dollar && replace_unquoted(env_block, &replacement) < 0)
// 		return (-1);
// 	else if (env_block->f == dollar_dquote
// 			&& replace_dquoted(env_block, &replacement) < 0)
// 		return (-1);
// 	else
// 		replacement = NULL;
// 	block_lst_old = *block_lst;
// 	*block_lst = (*block_lst)->next;
// 	insert_in_list(block_lst_prev, replacement, block_lst);
// 	ft_lstdelone(block_lst_old, destroy_block);
// 	return (1);
// }

// static int	split_block_lst(t_list *block_lst, t_list **text_ast_lst)
// {
// 	t_status	status;
// 	t_ast		*text_ast;

// 	*text_ast_lst = NULL;
// 	while (1)
// 	{
// 		status = parse_text(&text_ast, &block_lst);
// 		if (status == STATUS_ERROR || !text_ast)
// 			break ;
// 		if (!ft_lstadd_back_content(text_ast_lst, text_ast))
// 		{
// 			destroy_ast(&text_ast);
// 			return (-1);
// 		}
// 	}
// 	if (status == STATUS_OK)
// 		return (1);
// 	else
// 		return (-1);
// }

static int	replace_env_text(t_list **text_lst, t_list **redir_blocks)
{
	t_list	*lst;
	t_list	*lst_prev;

	lst = *text_lst;
	lst_prev = NULL;
	while (lst)
	{
		// printf("lst:\n");
		// print_list_one(lst);
		// print_address(lst);
		// printf("lst_prev:\n");
		// print_list_one(lst_prev);
		// print_address(lst_prev);
		if (is_dollar_lst(lst) || is_tilde_lst(lst))
		{
			if (!lst_prev)
			{
				if (replace_env_block(&lst_prev, lst, text_lst, redir_blocks) < 0)
					return (-1);
			}
			else if (replace_env_block(&lst_prev, lst, NULL, redir_blocks) < 0)
				return (-1);
			if (!lst_prev)
				break ;
			lst = lst_prev->next;
		}
		else
		{
			lst_prev = lst;
			lst = lst->next;
		}
	}
	return (1);
}

// static int	is_dollar_ptr(void *content)
// {
// 	return (is_dollar((t_block *)content));
// }

// static int	replace_env_list(t_list	**text_ast_lst, int allow_any_replacement)
// {
// 	t_list	*lst;
// 	t_list	*lst_prev;
// 	t_ast	*text_ast;
// 	t_list	*text_ast_repl;

// 	lst = *text_ast_lst;
// 	lst_prev = NULL;
// 	while (lst)
// 	{
// 		text_ast = (t_ast *)lst->content;
// 		text_ast_repl = NULL;
// 		if (ft_lstany(text_ast->expr.text, is_dollar_ptr))
// 		{
// 			if (replace_env_text(text_ast, &text_ast_repl) < 0)
// 				return (-1);
// 			if (!allow_any_replacement && ft_lstsize(text_ast_repl) =! 1)
// 			{
				
// 			}
// 				return ()
// 			insert_in_list(&lst_prev, text_ast_repl, )
// 		}
// 		if (!text_ast_repl)

		
// 	}
// }

static int	invalid_file_name(t_list *file_name)
{
	if (!file_name)
		return (1);
	return (ft_lstany(file_name, is_space_ptr));
}

static int	replace_env_cmd(t_ast *cmd_ast)
{
	t_list	*redir_list;
	t_ast	*redir_ast;
	t_list	*redir_fname;
	t_list	*redir_blocks;
	int		ret;

	if (replace_env_text(&cmd_ast->expr.command.text_list, NULL) < 0)
		return (-1);
	redir_blocks = NULL;
	redir_list = cmd_ast->expr.command.redir_list;
	while (redir_list)
	{
		redir_ast = (t_ast *)redir_list->content;
		if (replace_env_text(&redir_ast->expr.redir.file_name, &redir_blocks) < 0)
			return (-1);
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

int	replace_env(t_ast *cmdchain_ast)
{
	if (cmdchain_ast->type == command_expr)
	{
		if (replace_env_cmd(cmdchain_ast) < 0)
			return (-1);
	}
	else if (cmdchain_ast->type == binary_expr)
	{
		if (replace_env(cmdchain_ast->expr.binary.left) < 0)
			return (-1);
		if (replace_env(cmdchain_ast->expr.binary.right) < 0)
			return (-1);
	}
	return (1);
}
