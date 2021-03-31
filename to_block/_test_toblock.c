#include "to_block.h"




void	ft_test(char *line)
{
	t_list *final_l;
	final_l = NULL;
	to_block(line, &final_l);
	while(final_l != NULL)
	{
		printf("dedans |%s|\n",((t_block*)(final_l->content))->str);
		final_l = final_l->next;
	}
}
int main(int ag, char *av[])
{

//	ft_test("\"\'s\'\"");
//	ft_test("\"\\\'\"");
//	ft_test("\"\\\"\"");
	ft_test("\"\\$test\"");
}
