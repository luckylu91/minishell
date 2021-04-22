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

// int	list_content(char *dir_name, t_list **fname_lst)
// {
// 	DIR	*dir_stream;
// 	struct dirent	*file;
// 	char	*fname;

// 	*fname_lst = NULL;
// 	dir_stream = opendir_err(dir_name);
// 	if (!dir_stream)
// 		return (-1);
// 	file = readdir(dir_stream);
// 	while (file)
// 	{
// 		fname = pathjoin(dir_name, file->d_name);
// 		if (!fname || !ft_lstadd_back_content(fname_lst, fname))
// 		{
// 			ft_lstclear(fname_lst, free);
// 			return (-1);
// 		}
// 		file = readdir(dir_stream);
// 	}
// 	return (1);
// }
