#include "to_block.h"

char	*block_flags_str(t_block *block)
{
	enum flags f = block->f;

	switch(f)
	{
		case none:
			return (ft_strdup("none"));
		case dollar:
			return (ft_strdup("dollar"));
		case dollar_num:
			return (ft_strdup("dollar_num"));
		case dollar_dquote:
			return (ft_strdup("dollar_dquote"));
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
void	ft_test(char *line)
{
	t_list *final_l;
	final_l = NULL;
	to_block(line, &final_l);
	while(final_l != NULL)
	{
		printf("str = |%s| flag = |%s|\n",((t_block*)(final_l->content))->str, block_flags_str((t_block*)(final_l->content)));
		final_l = final_l->next;
	}
}

void	ft_test_redirection()
{
	printf("\n TEST REDIRECTION\n");
	ft_test("$a3> patate");
	ft_test("$\"a3\"> patate");
	ft_test("$\'a3\'> patate");
	ft_test("ls 33> test.txt");
	ft_test("ls t33> test.txt");
}
void	ft_test_dollar()
{

	printf("\n TEST DOLLAR\n");

	ft_test("\"$test\"");
	ft_test("try $test ");
	ft_test("try    \\$test");
	ft_test("try $\'test\'");
	ft_test("try $\"test\"");
	ft_test("try$test");

	ft_test("\'try\'$test");
	ft_test("\"try\'$test\"");
	ft_test("try a$\"test\"");
	ft_test("try a$test");
	ft_test("try $");
	ft_test("try $\'a\'");
}
void	ft_test_dollar_bs()
{
	printf("\n TEST DOLLAR BS\n");
	ft_test("$\\a");
	ft_test("$\'\\a\'a");

	ft_test("\"\\$test\"");
	ft_test("\"\\$\"");
	
	ft_test("\"\\$bite\"");

	ft_test("\"$bite\"");

}

void 	ft_test_combo_quote()
{
	printf("\nTEST COMBO QUOTE \n");
	ft_test("\"\'s\'\"");
	ft_test("\"\\\'\"");
	ft_test("\"\\\"\"");

	ft_test("\"  \\\"   \"");
	ft_test("\"\\s\"");
	ft_test("\"\\$\"");

	ft_test("\"\\$test\"");

}
int main(int ag, char *av[])
{
	//char b[1];
	int i;
	int r;
	r = 1;
	i = 1;
//	while(r)
//	{
//		read(0, b, 1);
//	printf("|%s| ici\n",b);
//	}
//
//	ft_test_combo_quote();
//	ft_test_redirection();
	ft_test_dollar();
	ft_test_dollar_bs();
	//ft_test("echo a > b | ls pourqoui -pas > lalali ; cat $NOOOOON");
}
