#include <stdio.h>
#include <stdlib.h>
#include "ast_api.h"

char *block_flags_str(t_block *block)
{
	enum flags f = block->f;

	switch(f)
	{
		case none:
			return (ft_strdup("none"));
		case error:
			return (ft_strdup("error"));
		case space:
			return (ft_strdup("space"));
		case spe:
			return (ft_strdup("spe"));
		default:
			return (ft_strdup("invalid_flag"));
	}
}

void print_block(void *block_ptr)
{
	t_block	*block = (t_block*)block_ptr;
	char	*flags_str = NULL;
	char	*block_str = NULL;

	if (!block)
		return ;
	flags_str = block_flags_str(block);
	block_str = block->str ? ft_strdup(block->str) : ft_strdup("__null_str__");
	if (!flags_str || !block_str)
	{
		free(flags_str);
		free(block_str);
		fprintf(stderr, "<malloc error in print_block>");
		return ;
	}
	printf("<(%s)%s> -> ", flags_str, block_str);
}

void print_block_list(t_list *lst)
{
	ft_lstiter(lst, print_block);
	printf("END\n");
}

int test1()
{
	t_list *blocks;

	blocks = NULL;
	ft_lstadd_back_content(&blocks, create_block(none, "UnBloc"));
	print_block_list(blocks);
	ft_lstclear(&blocks, &destroy_block);
	return (0);
}

int test2()
{
	t_list *blocks;

	blocks = NULL;
	ft_lstadd_back_content(&blocks, create_block(none, "Bloc1"));
	ft_lstadd_back_content(&blocks, create_block(none, "Bloc2"));
	print_block_list(blocks);
	ft_lstclear(&blocks, &destroy_block);
	return (0);
}

int main()
{
	test1();
	test2();
}
