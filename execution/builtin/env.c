#include "execution.h"

int	our_env(char **tab_env)
{
	int i;

	i = 0;
	while (tab_env[i] != NULL)
	{
		printf("%s\n",tab_env[i]);
		i++;
	}
	return 1;
}
