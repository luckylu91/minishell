#include "libft.h"
#include <stdio.h>

int g_exit_code;

int	*new_int(int i)
{
	int *res = malloc(sizeof(int));
	if (res)
		*res = i;
	return res;
}

int	int_at(t_bilist *blst)
{
	if (!blst)
		return (-8000);
	return (*(int *)blst->content);
}

int main()
{
	t_bilist *blst1 = NULL;

	ft_bilstadd_back_content(&blst1, new_int(2));
	ft_bilstadd_front_content(&blst1, new_int(1));
	ft_bilstadd_front_content(&blst1, new_int(0));
	ft_bilstadd_back_content(&blst1, new_int(3));

	printf("int at head : %d\n", int_at(blst1));
	printf("int at last : %d\n", int_at(ft_bilstlast(blst1)));
	int i = 0;
	while (blst1->next)
	{
		printf("int at %d : %d\n", i, int_at(blst1));
		blst1 = blst1->next;
		i++;
	}
	printf("int at %d : %d\n", i, int_at(blst1));
	while (blst1->prev)
	{
		printf("int at %d : %d\n", i, int_at(blst1));
		blst1 = blst1->prev;
		i--;
	}
	i = 0;
	while (i < 10)
	{
		printf("i = %d : %d\n", i, int_at(blst1));
		blst1 = ft_bilststep_blocking(blst1, 1);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		printf("i = %d : %d\n", i, int_at(blst1));
		blst1 = ft_bilststep_blocking(blst1, -1);
		i++;
	}
}