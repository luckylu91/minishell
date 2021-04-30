#include <stdlib.h>
#include <stdio.h>

#include "libft.h"

void print_int(void *i)
{
	printf("%d", *(int *)i);
}

void print_int_list(t_list *lst)
{
	ft_lstiter(lst, print_int);
}

void before_exit(void *context)
{
	printf("exiting...\n");
}

int main()
{
	t_list *lst = NULL;

	ft_lstdupint_back(&lst, 0);
	print_int_list(lst);
	ft_lstdupint_back(&lst, 0);
	print_int_list(lst);
	ft_lstdupint_back(&lst, 0);
	print_int_list(lst);
	ft_get_set_exit_fun(before_exit);
	ft_before_exit();
	printf("THE END\n");
}
