#include "execution.h"
#include <stdio.h>

void print_list_one(t_list *l)
{
	if (!l)
		printf("(null)\n");
	else
		printf("content = %d, next = %p\n", *(int*)l->content, l->next);
}

void print_adresses(t_list *array[6], char *names[6])
{
	int i;

	i = -1;
	while (++i < 6)
		printf("Address of list %s:\t%p\n", names[i], array[i]);
	i = -1;
	while (++i < 6)
	{
		printf("List %s:\t", names[i]);
		print_list_one(array[i]);
	}
}

void	*itoa_ptr(void *iptr)
{
	int i = *(int*)iptr;
	return (ft_itoa(i));
}

void print_list(t_list *lst)
{
	t_list	*charlist;
	char	*str;

	charlist = ft_lstmap(lst, itoa_ptr, free);
	str = ft_lststrjoin(charlist, ", ", "[", "]");
	ft_lstclear(&charlist, free);
	printf("%s", str);
	free(str);
}

int main()
{
	t_list	*l1 = NULL;
	t_list	*lmid = NULL;
	t_list	*l2 = NULL;
	t_list	*lprev = NULL;
	t_list	*l = NULL;
	t_list	*lbeg = NULL;
	char	*names[6] = {"l1", "lmid", "l2", "lprev", "l", "lbeg"};

	setbuf(stdout, NULL);
	ft_lstdupint_back(&l1, 0);
	ft_lstdupint_back(&l1, 1);
	ft_lstdupint_back(&lmid, 2);
	ft_lstdupint_back(&lmid, 3);
	ft_lstdupint_back(&l2, 4);
	ft_lstdupint_back(&l2, 5);

	lprev = l1->next;
	l = l2;

	t_list	*array[6] = {l1, lmid, l2, lprev, l, lbeg};
	print_adresses(array, names);
	insert_in_list(&lprev, l, lmid, &lbeg);
	printf("\n---\n\n");

	t_list	*array2[6] = {l1, lmid, l2, lprev, l, lbeg};
	print_adresses(array2, names);
	print_list(l1);
}