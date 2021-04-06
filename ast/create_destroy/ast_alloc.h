#ifndef AST_ALLOC_H
#define AST_ALLOC_H

#include "ast_api.h"

t_block	*create_block(enum flags f, char *str);
void	destroy_block(void *block_ptr);
void	destroy_block_lst(t_list **block_lst);
t_block	*dup_block(t_block *block);

int	create_ast(t_ast **result_ast, t_ast_type type);
int	create_ast_if_needed(t_ast **result_ast, t_ast_type type);
int new_string_ast(t_ast **result_ast, t_block *string_block);
int	new_redir_ast(t_ast **result_ast, t_block *redir_op, t_ast *file_name);
//int create_cmd_ast(t_ast **result_ast, t_ast *text_ast);

void	destroy_string_ast(t_ast *nnull_ast);
void	destroy_text_ast(t_ast *nnull_ast);
void	destroy_redir_ast(t_ast *nnull_ast);
void	destroy_unary_ast(t_ast *nnull_ast);
void	destroy_binary_ast(t_ast *nnull_ast);
void	destroy_command_ast(t_ast *nnull_ast);
void	destroy_ast(t_ast **ast);
void	destroy_ast_list(t_list **ast_lst);

#endif