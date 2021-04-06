#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast_api.h"

char	*pathjoin(char *dirname, char *fname);
int	list_content(char *dir_name, t_list **fname_lst);

#endif