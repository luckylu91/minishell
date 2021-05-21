#ifndef AST_ALLOC_H
# define AST_ALLOC_H

# include "ast_api.h"

t_ast	*create_ast(t_ast_type type);
t_ast	*new_redir_ast(t_block *redir_op, t_list *file_name);

t_block	*create_block(enum e_flags f, char *str);
void	destroy_block(void *block_ptr);
void	destroy_block_lst(t_list **block_lst);
t_block	*dup_block(t_block *block);

void	destroy_text_ast(t_ast *nnull_ast);
void	destroy_redir_ast(t_ast *nnull_ast);
void	destroy_binary_ast(t_ast *nnull_ast);
void	destroy_command_ast(t_ast *nnull_ast);
void	destroy_ast(t_ast **ast);
void	destroy_ast_list(t_list **ast_lst);

#endif