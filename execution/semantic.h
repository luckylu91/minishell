#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast_api.h"
#include <dirent.h>
#include <sys/errno.h>
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
// int	list_content(char *dir_name, t_list **fname_lst);
int	dir_contains(char *dir_name, char *fname);
char	*search_cmd(char **path_dirnames, char *cmd_name);

#endif
