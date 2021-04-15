#include "search.h"

char	*search_cmd(char **path_dirnames, char *cmd_name)
{
	int i;

	i = 0;
	while (path_dirnames[i])
	{
		if (dir_contains(path_dirnames[i], cmd_name))
			return (pathjoin(path_dirnames[i], cmd_name));
		i++;
	}
	return (NULL);
}
