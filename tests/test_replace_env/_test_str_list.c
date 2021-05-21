#include "execution.h"
#include "to_block.h"

int main()
{
	t_list *block_lst;
	t_list *str_lst;
	int ret;

	setbuf(stdout, NULL);
	to_block("echo a b c", &block_lst);
	printf("to_block finished\n");
	
	print_block_list(block_lst);
	printf("\n");
	ret = to_string_list(block_lst, &str_lst);
	printf("return = %d\n", ret);
	printf("size: %d\n", ft_lstsize(str_lst));
	printf("%s\n", ft_lststrjoin(str_lst, "|", NULL, NULL));

	ft_lstadd_back_content(&block_lst, create_block(none, "aca"));
	print_block_list(block_lst);
	printf("\n");
	ret = to_string_list(block_lst, &str_lst);
	printf("return = %d\n", ret);
	printf("size: %d\n", ft_lstsize(str_lst));
	printf("%s\n", ft_lststrjoin(str_lst, "|", NULL, NULL));

}