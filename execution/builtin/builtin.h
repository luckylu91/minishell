#ifndef EXECUTION_H
#define EXECUTION_H

#include "libft.h"
#include "searchdir.h"
#include "error.h"
#include "to_block.h"
#include <fcntl.h>
#include "ast_api.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
int	cd(char **argv);
int	echo(char **argv);
int	export(char **argv, char ***our_env);
int	pwd(char **argv);
#endif
