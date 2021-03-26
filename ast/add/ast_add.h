/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:50:01 by lzins             #+#    #+#             */
/*   Updated: 2021/03/26 09:59:22 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_ADD_H
#define AST_ADD_H

#include "ast.h"

int	addback_block(t_list **alst, t_block *block);
int	add_textitem_totext(t_ast **text_ast, t_list *item_lst);
int	add_textredir_tocmd(t_ast **cmd_ast, t_ast *text_redir_ast);

#endif