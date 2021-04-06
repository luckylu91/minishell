
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
		case dollar:
			return (ft_strdup("dollar"));
		default:
			return (ft_strdup("INVALID_FLAG"));
	}
}

void	print_block(void *block_ptr)
{
	t_block	*block = (t_block*)block_ptr;
	char	*flags_str = NULL;

	if (!block)
	{
		printf("<null_block>");
		return ;
	}
	flags_str = block_flags_str(block);
	if (!flags_str)
		fprintf(stderr, "<malloc error>");
	else
		printf("<(%s)%s>", flags_str, block->str);
	free(flags_str);
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
