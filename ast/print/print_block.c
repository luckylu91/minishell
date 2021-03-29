
#include "ast_api.h"

char	*block_flags_str(t_block *block)
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

void	print_block(void *block_ptr)
{
	t_block	*block = (t_block*)block_ptr;
	char	*flags_str = NULL;
	char	*block_str = NULL;

	if (!block)
		return ;
	flags_str = block_flags_str(block);
	block_str = block->str ? ft_strdup(block->str) : ft_strdup("__null_str__");
	if (!flags_str || !block_str)
		fprintf(stderr, "<malloc error>");
	else
		printf("<(%s)%s>", flags_str, block_str);
	free(flags_str);
	free(block_str);
}

static void	print_block_and_arrow(void *block_ptr)
{
	print_block(block_ptr);
	printf(" -> ");
}

void	print_block_list(t_list *lst)
{
	ft_lstiter(lst, print_block_and_arrow);
	printf("END");
}
