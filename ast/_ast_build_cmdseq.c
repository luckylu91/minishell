/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_build_cmdseq.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:36:09 by lzins             #+#    #+#             */
/*   Updated: 2021/04/02 00:06:52 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	tokens_cmd1(t_list **tokens)
{
	ft_lstadd_back_content(tokens, create_block(none, "ls"));
	ft_lstadd_back_content(tokens, create_block(space, " "));
	ft_lstadd_back_content(tokens, create_block(none, "arg"));
	ft_lstadd_back_content(tokens, create_block(spe, ">"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file"));
}

void	tokens_cmd2(t_list **tokens)
{
	ft_lstadd_back_content(tokens, create_block(none, "ls"));
	ft_lstadd_back_content(tokens, create_block(spe, ">"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file"));
	ft_lstadd_back_content(tokens, create_block(none, "arg"));
}

void	tokens_cmd3(t_list **tokens)
{
	ft_lstadd_back_content(tokens, create_block(none, "ls"));
	ft_lstadd_back_content(tokens, create_block(space, " "));
	ft_lstadd_back_content(tokens, create_block(none, "arg1"));
	ft_lstadd_back_content(tokens, create_block(spe, ">"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file1"));
	ft_lstadd_back_content(tokens, create_block(none, "arg2"));
	ft_lstadd_back_content(tokens, create_block(spe, "2<<"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file2"));
	ft_lstadd_back_content(tokens, create_block(none, "arg3"));
	ft_lstadd_back_content(tokens, create_block(none, "arg4"));
}

void tokens1(t_list **tokens)
{
	*tokens = NULL;
	tokens_cmd1(tokens);
	ft_lstadd_back_content(tokens, create_block(spe, "|"));
	tokens_cmd2(tokens);
	ft_lstadd_back_content(tokens, create_block(spe, ";"));
	tokens_cmd3(tokens);
}

static void print_ast_ptr(void *ast_ptr)
{
	printf("\n");
	print_ast((t_ast*)ast_ptr);
	printf("\n\n---");
}

static void destroy_ast_ptr(void *ast_ptr)
{
	destroy_ast((t_ast**)&ast_ptr);
}

int build_print_destroy_ast(t_list *tokens)
{
	t_list	*ast_seq;

	if (parse_cmdseq(&ast_seq, tokens) != STATUS_OK)
		return (-1);
	ft_lstiter(ast_seq, print_ast_ptr);
	printf("\n");
	ft_lstclear(&ast_seq, destroy_ast_ptr);
	return (1);
}

int test_build(t_list *tokens)
{
	int	ret;

	ret = build_print_destroy_ast(tokens);
	printf("ret = %d\n", ret);
	return (ret);
}

typedef struct {
	char	*redirop_str;
	char	*file_name;
}	t_redir_args;

int main()
{
	int		i;
	t_list	*tokens;
	setbuf(stdout, NULL);

	tokens1(&tokens);
	test_build(tokens);
}
