/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_block.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:45:58 by hgallien          #+#    #+#             */
/*   Updated: 2021/04/06 14:09:00 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TO_BLOCK_H
#define TO_BLOCK_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

enum flags {none, error, space, spe, dollar, dollar_num, dollar_dquote};
 void    to_block(char *line, t_list **final_l);
typedef struct s_var_toblock
{
	int i;
	int spe;
	int end_while;
	enum flags f;
}				t_var_toblock;
typedef struct		s_block
{
	char *str;
	enum flags f;
}					t_block;

#endif
