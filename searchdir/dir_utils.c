#include "searchdir.h"

DIR	*opendir_err(char *dir_name)
{
	DIR	*dir_stream;

	dir_stream = opendir(dir_name);
	if (!dir_stream)
		printf("%s\n", strerror(errno));
	return (dir_stream);
}

int	closedir_err(DIR *dir)
{
	if (closedir(dir) == -1)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	return (1);
}

char	*pathjoin(char *dirname, char *fname)
{
	char	*res;
	char	*res_mov;

	res = ft_calloc(ft_strlen(dirname) + 1 + ft_strlen(fname) + 1, sizeof(char));
	if (!res)
		return (NULL);
	res_mov = ft_strcat_and_move(res, dirname);
	res_mov = ft_strcat_and_move(res_mov, "/");
	ft_strcat(res_mov, fname);
	return (res);
}

int	is_dir(char *pathbase, char *name)
{
	struct stat	buf;
	char		*path;
	int			ret;

	if (pathbase)
		path = pathjoin(pathbase, name);
	else if (name)
		path = ft_strdup(name);
	else
		return (0);
	ret = stat(path, &buf);
	wrap_free(path);
	return (S_ISDIR(buf.st_mode));
}
