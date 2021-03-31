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
	//create_ast(&text_ast, text_expr);
	add_textitem_totext(&text_ast, create_block(none, "Bloc1"));
	add_textitem_totext(&text_ast, create_block(none, "Bloc2"));
	print_ast(text_ast);
	printf("\n");
	return (0);
}

int test_ast2()
{
	t_ast *cmd_ast;
	t_ast *text_ast;
	t_ast *redir_ast;
	t_ast *text2_ast;

	//create_ast(&text_ast, text_expr);
	text_ast = NULL;
	add_textitem_totext(&text_ast, create_block(none, "Bloc1"));
	add_textitem_totext(&text_ast, create_block(spe, "*"));
	add_textitem_totext(&text_ast, create_block(none, "Bloc2"));

	new_redir_ast(&redir_ast, create_block(spe, ">"), create_block(none, "file_test")); // todo test fd

	text2_ast = NULL;
	add_textitem_totext(&text2_ast, create_block(none, "AKadok"));

	cmd_ast = NULL;
	add_textredir_tocmd(&cmd_ast, text_ast); // TODO if no text first ?
	add_textredir_tocmd(&cmd_ast, redir_ast);
	add_textredir_tocmd(&cmd_ast, text2_ast);
	print_ast(cmd_ast);
	printf("\n");
	return (0);
}

int main()
{

	setbuf(stdout, NULL);
	test_blocks1();
	test_blocks2();
	test_ast1();
	test_ast2();
}
