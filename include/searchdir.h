#ifndef SEARCHDIR_H
# define SEARCHDIR_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/stat.h>

char	*our_getcwd(void);

DIR		*opendir_err(char *dir_name);
int		closedir_err(DIR *dir);
char	*pathjoin(char *dirname, char *fname);
int		dir_contains(char *dir_name, char *fname);
int		cwd_contains(char *fname);
int		list_dir(char *dir_name, t_list **alst);
char	*search_cmd(char **path_dirnames, char *cmd_name);
int		is_dir(char *pathbase, char *name);
void	separate_last_slash(char *str, char **str_path, char **str_end);

#endif
