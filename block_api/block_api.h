#ifndef BLOCK_API
#define BLOCK_API

#include <stdlib.h>

#include "libft.h"
#include "to_block.h"
#include <unistd.h>

// enum flags {none, error, space, spe, dollar, dollar_num};
// typedef struct s_var_toblock
// {
// 	int i;
// 	int spe;
// 	int end_while;
// 	enum flags f;
// }				t_var_toblock;
// typedef struct		s_block
// {
// 	char *str;
// 	enum flags f;
// }					t_block;

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
void	parse_redirop(t_block *redirop, int *fd, char **symbol_begin);

int	is_chainop(t_block *block);
int	is_chainop_lst(t_list *block_lst);

int	is_wildcard(t_block *block);
int	is_wildcard_lst(t_list *block_lst);

int is_eof(t_block *block);
int is_eof_lst(t_list *block_lst);

int	is_text(t_block *block);
int	is_text_lst(t_list *block_lst);

#endif
