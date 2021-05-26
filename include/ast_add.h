/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:50:01 by lzins             #+#    #+#             */
/*   Updated: 2021/05/26 15:38:50 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_ADD_H
# define AST_ADD_H

# include "ast_api.h"

void	add_textitem_totext(t_ast **text_ast, t_block *block);
void	add_textredir_tocmd(t_ast **cmd_ast, t_ast *text_redir_ast);
void	add_cmd_tochain(t_ast **cmdchain_ast, t_ast *cmd_ast, t_block *chainop);
void	addback_space_block(t_list **alst);
void	addback_none_block_nodup(t_list **alst, char *str);

#endif