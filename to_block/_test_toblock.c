#include "to_block.h"

int main(int ag, char *av[])
{

	t_list *final_l;
	final_l = NULL;
	printf("sa mere \n");
	to_block("$\\test", &final_l);
	while(final_l != NULL)
	{
		printf("dedans |%s|\n",((t_block*)(final_l->content))->str);
		final_l = final_l->next;
	}
}
