#include "execution.h"

int main(int argc, char **argv)
{
	char **args;
	int i;

	args = ft_calloc(argc, sizeof(char *));
	i = 0;
	while (++i < argc)
	{
		args[i - 1] = argv[i];
	}
	export(args);
}