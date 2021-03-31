/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:50:01 by lzins             #+#    #+#             */
/*   Updated: 2021/03/31 12:14:07 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_ADD_H
#define AST_ADD_H

#include "ast_api.h"

int	add_textitem_totext(t_ast **text_ast, t_block *block);
int	add_textredir_tocmd(t_ast **cmd_ast, t_ast *text_redir_ast);
int add_cmd_tochain(t_ast **cmdchain_ast, t_ast *cmd_ast, t_block *chainop);

#endif