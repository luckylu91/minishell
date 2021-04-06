#include "semantic.h"

int main()
{
	t_list	*fname_lst = NULL;
	int	ret;
	char	*fname_list_str;
	char	*dir_name = "ast";

	ret = list_content(dir_name, &fname_lst);
	printf("ret = %d\n", ret);
	fname_list_str = ft_lststrjoin(fname_lst, ", ", "", "");
	printf("files in %s: %s\n", dir_name, fname_list_str);
}
