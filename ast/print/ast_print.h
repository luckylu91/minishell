#ifndef AST_PRINT_H
#define AST_PRINT_H

#include "ast_api.h"

char	*block_flags_str(t_block *block);
char	*block_string(t_block *block);
void	*block_string_ptr(void *block_ptr);
void	print_block(void *block_ptr);
void	print_block_list(t_list *lst);
void	print_ast(t_ast *ast);
void	print_ast_list(t_list *ast_lst);

#endif