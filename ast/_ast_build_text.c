/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_build_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:58:23 by lzins             #+#    #+#             */
/*   Updated: 2021/03/31 14:51:31 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_list	*tokens00(void)
{
	return (NULL);
}

t_list	*tokens01(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, ";"));
	return (tokens);
}

t_list	*tokens1(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(none, "Hello World !"));
	return (tokens);
}

t_list	*tokens2(void)
{
	t_list *tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(none, "Bloc1"));
	ft_lstadd_back_content(&tokens, create_block(spe, "*"));
	ft_lstadd_back_content(&tokens, create_block(none, "Bloc2"));
	return (tokens);
}

int build_print_destroy_ast(t_list *tokens)
{
	t_list	*tokens_moving;
	t_ast	*ast;

	tokens_moving = tokens;
	if (parse_text(&ast, &tokens_moving) != STATUS_OK)
		return (-1);
	print_ast(ast);
	printf("\n");
	printf("Next token : ");
	if (tokens_moving)
		printf("NULL");
	else
		print_block(block_at(tokens_moving));
	printf("\n\t---\n");
	destroy_ast(&ast);
	return (1);
}

int test_build(t_list *(*tokens_fun)(void))
{
	t_list *tokens;
	int	ret;

	tokens = (*tokens_fun)();
	ret = build_print_destroy_ast(tokens);
	destroy_block_lst(&tokens);
	return (ret);
}

int main()
{
	t_list *tokens;

	test_build(tokens00);
	test_build(tokens01);
	test_build(tokens1);
	test_build(tokens2);
}
