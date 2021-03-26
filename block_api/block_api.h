#ifndef BLOCK_API
#define BLOCK_API

#include "to_block.h"
#include <stdlib.h>

t_block	*block_at(t_list *block_lst);

int is_special(t_block *block);
int is_special_lst(t_list *block_lst);

int	is_space(t_block *block);
int	is_space_lst(t_list *block_lst);

int	is_semicol(t_block *block);
int	is_semicol_lst(t_list *block_lst);

int	is_pipe(t_block *block);
int	is_pipe_lst(t_list *block_lst);

int	is_chainop(t_block *block);
int	is_chainop_lst(t_list *block_lst);

int	is_redirop(t_block *block);
int	is_redirop_lst(t_list *block_lst);

int	is_wildcard(t_block *block);

#endif