
#include <stdio.h>

char	**split_path(void);

int main()
{
	int i;
	char **res;

	i = 0;
	res = split_path();
	while (res[i] != NULL)
	{
		printf("|%s|\n", res[i]);
		i++;
	}

}
