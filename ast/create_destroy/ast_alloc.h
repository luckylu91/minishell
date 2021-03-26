#ifndef AST_ALLOC_H
#define AST_ALLOC_H

t_block *create_block(enum flags f, char *str);
t_block	*dup_block(t_block *block);

#endif