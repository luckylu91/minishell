/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_block.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:45:58 by hgallien          #+#    #+#             */
/*   Updated: 2021/05/27 14:23:09 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TO_BLOCK_H
# define TO_BLOCK_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

enum e_flags {
	none,
	error,
	space,
	spe,
	dollar,
	dollar_num,
	dollar_dquote,
	tilde
};

typedef struct s_var_toblock
{
	int				i;
	int				spe;
	int				end_while;
	int				tilde;
	enum e_flags	f;
}	t_var_toblock;

typedef struct s_block
{
	char			*str;
	enum e_flags	f;
}	t_block;

void	digit_quest(t_var_toblock *var, char *line,
			t_list **temp_l, t_list **final_l);
int		condition(char *line, t_var_toblock *var, t_list **temp_l);
void	test_intero(char *line, t_var_toblock *var,
			t_list **temp_l, t_list **final_l);
void	to_block(char *line, t_list **final_l);
void	in_double_quote(char *line, t_var_toblock *var,
			t_list **final_l, t_list **temp_l);
void	in_back_slash(char *line, t_var_toblock *var,
			t_list **temp_l);
void	in_back_slash_dquote(char *line, t_var_toblock *var,
			t_list **temp_l);
void	ft_dollar(t_var_toblock *var, char *line,
			t_list **temp_l, t_list **final_l);
void	ft_dollar_dquote(char *line, t_var_toblock *var,
			t_list **final_l, t_list **temp_l);
void	in_quote(char *line, t_var_toblock *var, t_list **final_l,
			t_list **temp_l);
void	in_tilde(char *line, t_var_toblock *var, t_list **temp_l);
void	redirection(t_var_toblock *var, char *line,
			t_list **final_l, t_list **temp_l);
int		test_redir(char *line, t_var_toblock *var, t_list *temp_l);
int		is_separator(char *c);
int		is_separator_for_dollar(char *c);
void	handle_separator(t_var_toblock *var, char *line,
			t_list **final_l, t_list **temp_l);
t_block	*new_block(char *c, enum e_flags f);
void	handle_space(t_var_toblock *var, t_list **final_l,
			t_list **temp_l, char *line);
char	*list_to_string(t_list *l);
void	temp_to_final(t_list **final_l, t_list **temp_l, enum e_flags f);
void	str_to_list(char *str, t_list **temp_l);
#endif
