#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int null_or_empty(void *str)
{
	if (!str || *(char*)str == '\0')
		return (1);
	return (0);
}

int test_no_empty(t_list *tokens)
{
	return (!ft_lstany(tokens, null_or_empty));
}