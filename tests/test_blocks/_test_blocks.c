#include "minishell.h"

void ft_putendl(void *str)
{
	ft_putendl_fd(str, STDOUT_FILENO);
}

void	strlen_max(void *str, void *max)
{
	int	len;

	len = ft_strlen(str);
	if (len > *(int *)max)
		*(int *)max = len;
}

int	startswith(char *str, char *prefix)
{
	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

int main()
{
	t_list *blocks;
	t_list *files;
	char *cwd;
	int max_len;

	setbuf(stdout, NULL);
	to_block("echo \"$", &blocks);
	print_block_list(blocks);
	cwd = our_getcwd();
	list_dir(cwd, &files);
	max_len = -1;
	ft_lstiter(files, &max_len, strlen_max);
	printf("max_len : %d\n", max_len);
	ft_lstfilter(
		&files,
		((t_block *)ft_lstlast(blocks)->content)->str,
		(t_bool_fun)startswith, wrap_free
	);
	ft_lstiter(files, NULL, ft_putendl_fd);
}