/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ast_build_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:41:10 by lzins             #+#    #+#             */
/*   Updated: 2021/03/31 17:38:04 by lzins            ###   ########lyon.fr   */
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

	ft_lstadd_back_content(&tokens, create_block(none, "lalala"));
	return (tokens);
}

t_list	*tokens02(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, ";"));
	return (tokens);
}

t_list	*tokens1a(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, "<"));
	return (tokens);
}

t_list	*tokens1b(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, ">"));
	return (tokens);
}

t_list	*tokens1c(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, "<<"));
	return (tokens);
}

t_list	*tokens1d(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, ">>"));
	return (tokens);
}

t_list	*tokens1e(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, "5<"));
	return (tokens);
}

t_list	*tokens1f(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, "6>"));
	return (tokens);
}

t_list	*tokens1g(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, "7<<"));
	return (tokens);
}

t_list	*tokens1h(void)
{
	t_list	*tokens = NULL;

	ft_lstadd_back_content(&tokens, create_block(spe, "8>>"));
	return (tokens);
}

t_list	*tokens2a(void)
{
	t_list	*tokens = tokens1a();

	ft_lstadd_back_content(&tokens, create_block(none, "fname"));
	return (tokens);
}

t_list	*tokens2b(void)
{
	t_list	*tokens = tokens1b();

	ft_lstadd_back_content(&tokens, create_block(none, "fname"));
	return (tokens);
}

t_list	*tokens2c(void)
{
	t_list	*tokens = tokens1c();

	ft_lstadd_back_content(&tokens, create_block(none, "fname"));
	return (tokens);
}

t_list	*tokens2d(void)
{
	t_list	*tokens = tokens1d();

	ft_lstadd_back_content(&tokens, create_block(none, "fname"));
	return (tokens);
}

t_list	*tokens2e(void)
{
	t_list	*tokens = tokens1e();

	ft_lstadd_back_content(&tokens, create_block(none, "fname"));
	return (tokens);
}

t_list	*tokens2f(void)
{
	t_list	*tokens = tokens1f();

	ft_lstadd_back_content(&tokens, create_block(none, "fname"));
	return (tokens);
}

t_list	*tokens2g(void)
{
	t_list	*tokens = tokens1g();

	ft_lstadd_back_content(&tokens, create_block(none, "fname"));
	return (tokens);
}

t_list	*tokens2h(void)
{
	t_list	*tokens = tokens1h();

	ft_lstadd_back_content(&tokens, create_block(none, "fname"));
	return (tokens);
}

t_list	*tokens3(void)
{
	t_list	*tokens = tokens2a();

	ft_lstadd_back_content(&tokens, create_block(none, "next"));
	return (tokens);
}

int build_print_destroy_ast(t_list *tokens)
{
	t_list	*tokens_moving;
	t_ast	*ast;


	printf("\t---\n");
	tokens_moving = tokens;
	if (parse_redir(&ast, &tokens_moving) != STATUS_OK)
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
	char	*valid_redirtab[100] = {
		">", ">>", "<", "<<", "3>", "4>>", "5<", "6<<",
		NULL
	};

	i = 0;
	while (valid_redirtab[i])
	{
		tokens = NULL;
		ft_lstadd_back_content(&tokens, create_block(spe, valid_redirtab[i]));
		test_build(tokens);
		ft_lstadd_back_content(&tokens, create_block(none, "fname"));
		test_build(tokens);
		ft_lstadd_back_content(&tokens, create_block(none, "next_token"));
		test_build(tokens);
		destroy_block_lst(&tokens);
		i++;
	}
}
