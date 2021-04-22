
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

char	*block_string(t_block *block)
{
	char	*block_str = NULL;
	char	*flags_str = NULL;
	int		ret;

	if (!block)
		return (ft_strdup("(null_block)"));
	flags_str = block_flags_str(block);
	asprintf(&block_str, "(<%s>%s)", flags_str, block->str);
	free(flags_str);
	return (block_str);
}

void	*block_string_ptr(void *block_ptr)
{
	return (block_string((t_block*)block_ptr));
}

void	print_block(void *block_ptr)
{
	char *block_str = block_string_ptr(block_ptr);

	ft_putstr_fd(block_str, STDOUT_FILENO);
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
