#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

DIR	*opendir_err(char *dir_name);
int	closedir_err(DIR *dir);
char	*pathjoin(char *dirname, char *fname);
int	dir_contains(char *dir_name, char *fname);
char	*search_cmd(char **path_dirnames, char *cmd_name);

#endif