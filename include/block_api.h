#ifndef BLOCK_API_H
# define BLOCK_API_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "to_block.h"

t_block	*block_at(t_list *block_lst);
char	*block_str_at(t_list *blocks);

int		is_special(t_block *block);
int		is_special_lst(t_list *block_lst);

int		is_space(t_block *block);
int		is_space_ptr(void *block_ptr);
int		is_space_lst(t_list *block_lst);

int		is_semicol(t_block *block);
int		is_semicol_lst(t_list *block_lst);

int		is_pipe(t_block *block);
int		is_pipe_lst(t_list *block_lst);

int		is_chainop(t_block *block);
int		is_chainop_lst(t_list *block_lst);

int		is_redirop(t_block *block);
int		is_redirop_lst(t_list *block_lst);
void	parse_redirop(t_block *redirop, int *fd, char **symbol_begin);

int		is_chainop(t_block *block);
int		is_chainop_lst(t_list *block_lst);

int		is_wildcard(t_block *block);
int		is_wildcard_lst(t_list *block_lst);

int		is_eof(t_block *block);
int		is_eof_lst(t_list *block_lst);

int		is_rawtext(t_block *block);
int		is_rawtext_lst(t_list *block_lst);

int		is_dollar(t_block *block);
int		is_dollar_lst(t_list *block_lst);

int		is_tilde(t_block *block);
int		is_tilde_lst(t_list *block_lst);

int		is_text(t_block *block);
int		is_text_lst(t_list *block_lst);

#endif
