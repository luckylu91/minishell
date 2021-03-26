/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_block.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgallien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:45:58 by hgallien          #+#    #+#             */
/*   Updated: 2021/03/25 17:07:21 by hgallien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

enum flags {none, error, space, spe};
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
