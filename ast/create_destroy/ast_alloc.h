#ifndef AST_ALLOC_H
#define AST_ALLOC_H

#include "ast_api.h"

t_block	*create_block(enum flags f, char *str);
void	destroy_block(void *block_ptr);
t_block	*dup_block(t_block *block);

int	create_ast(t_ast **result_ast, t_ast_type type);
int	create_ast_if_needed(t_ast **result_ast, t_ast_type type);


#endif