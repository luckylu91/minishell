#include "semantic.h"

int	dir_contains(char *dir_name, char *fname)
{
	DIR	*dir;
	struct dirent	*file;
	int	ret;

	dir = opendir_err(dir_name);
	if (!dir)
		return (-1);
	file = readdir(dir);
	ret = 0;
	while (file)
	{
		if (ft_strcmp(file->d_name, fname) == 0)
		{
			ret = 1;
			break ;
		}
		file = readdir(dir);
	}
	if (closedir_err(dir) == -1)
		return (-1);
	return (ret);
}
