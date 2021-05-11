#include "execution.h"

extern char	**environ;

int	copy_environ(char ***new_env_addr)
{
	int		i;

	i = 0;
	while (environ[++i]);
	*new_env_addr = NULL;
	*new_env_addr = ft_calloc(i + 1, sizeof(char *));
	if (!*new_env_addr)
		return (-1);
	i = -1;
	while (environ[++i])
	{
		(*new_env_addr)[i] = ft_strdup(environ[i]);
		if (!(*new_env_addr)[i])
		{
			while (--i >= 0)
				wrap_free((*new_env_addr)[i]);
			wrap_free(*new_env_addr);
			return (-1);
		}
	}
	return (1);
}
