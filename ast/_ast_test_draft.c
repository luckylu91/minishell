#include <stdio.h>
#include <stdlib.h>
#include "ast_api.h"

int test_blocks1()
{
	t_list *blocks;

	blocks = NULL;
	ft_lstadd_back_content(&blocks, create_block(none, "UnBloc"));
	print_block_list(blocks);
	printf("\n");
	ft_lstclear(&blocks, &destroy_block);
	return (0);
}

int test_blocks2()
{
	t_list *blocks;

	blocks = NULL;
	ft_lstadd_back_content(&blocks, create_block(none, "Bloc1"));
	ft_lstadd_back_content(&blocks, create_block(none, "Bloc2"));
	print_block_list(blocks);
	printf("\n");
	ft_lstclear(&blocks, &destroy_block);
	return (0);
}

int test_ast1()
{
	t_ast	*text_ast;

	text_ast = NULL;
	create_ast(&text_ast, text_expr);
	add_textitem_totext(&text_ast, create_block(none, "Bloc1"));
	add_textitem_totext(&text_ast, create_block(none, "Bloc2"));
	print_ast(text_ast);
	return (0);
}

int main()
{
	test_blocks1();
	test_blocks2();
	text_ast1();
}
