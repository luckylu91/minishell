#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include "minishell.h"

DIR	*opendir_err(char *dir_name);
int	closedir_err(DIR *dir);
char	*pathjoin(char *dirname, char *fname);
int	dir_contains(char *dir_name, char *fname);
int	list_dir(char *dir_name, t_list **alst);
char	*search_cmd(char **path_dirnames, char *cmd_name);
int		is_dir(char *pathbase, char *name);

#endif
