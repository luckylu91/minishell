#include "minishell.h"

int main()
{
	// struct stat	buf;
	// char		*path;
	// int			ret;

	// ret = stat("test_term", &buf);
	// printf("%x\n", buf.st_mode);

	printf("test_term is dir : %s\n", is_dir(NULL, "test_term") ? "T":"F");
}