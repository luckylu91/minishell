/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:02:41 by lzins             #+#    #+#             */
/*   Updated: 2021/04/21 11:24:16 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "libft.h"
#include "searchdir.h"
#include "error.h"
#include "to_block.h"
#include "ast_api.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	replace_unquoted(t_block *env_block, t_list **replacement);
int	replace_dquoted(t_block *env_block, t_list **replacement);
int	replace_env(t_ast *cmdchain_ast);
//
void insert_in_list(t_list **lst_prev, t_list *lst, t_list *insert,
		t_list **begin);
// typedef struct s_both_fd
// {
// 	redir in;
// 	redir out;
// }				both_fd;

#endif
