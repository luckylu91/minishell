#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

typedef struct s_both_fd
{
	int in;
	int out;
}				both_fd;

DIR	*opendir_err(char *dir_name);
int	closedir_err(DIR *dir);
char	*pathjoin(char *dirname, char *fname);
int	dir_contains(char *dir_name, char *fname);
char	*search_cmd(char **path_dirnames, char *cmd_name);

#endif
