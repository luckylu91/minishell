/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_build_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:42:00 by lzins             #+#    #+#             */
/*   Updated: 2021/04/06 13:52:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	tokens1(t_list **tokens)
{
	*tokens = NULL;
	ft_lstadd_back_content(tokens, create_block(none, "ls"));
	ft_lstadd_back_content(tokens, create_block(space, " "));
	ft_lstadd_back_content(tokens, create_block(none, "arg"));
	ft_lstadd_back_content(tokens, create_block(spe, ">"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file"));
}

void	tokens2(t_list **tokens)
{
	*tokens = NULL;
	ft_lstadd_back_content(tokens, create_block(none, "ls"));
	ft_lstadd_back_content(tokens, create_block(spe, ">"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file"));
	ft_lstadd_back_content(tokens, create_block(none, "arg"));
}

void	tokens3(t_list **tokens)
{
	*tokens = NULL;
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

void	tokens4(t_list **tokens)
{
	*tokens = NULL;
	ft_lstadd_back_content(tokens, create_block(spe, ">"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file1"));
	ft_lstadd_back_content(tokens, create_block(spe, ">>"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file2"));
	ft_lstadd_back_content(tokens, create_block(none, "ls"));
	ft_lstadd_back_content(tokens, create_block(spe, "<"));
	ft_lstadd_back_content(tokens, create_block(none, "redir_file3"));
	ft_lstadd_back_content(tokens, create_block(space, " "));
	ft_lstadd_back_content(tokens, create_block(none, "arg"));
}

int build_print_destroy_ast(t_list *tokens)
{
	t_list	*tokens_moving;
	t_ast	*ast;


	printf("\t---\n");
	tokens_moving = tokens;
	if (parse_cmd(&ast, &tokens_moving) != STATUS_OK)
		return (-1);
	print_ast(ast);
	printf("\n");
	printf("Next token : ");
	if (!tokens_moving)
		printf("NULL");
	else
		print_block(block_at(tokens_moving));
	printf("\n");
	destroy_ast(&ast);
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
	tokens2(&tokens);
	test_build(tokens);
	tokens3(&tokens);
	test_build(tokens);
	tokens4(&tokens);
	test_build(tokens);
}
