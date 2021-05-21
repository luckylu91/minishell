/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_command_ast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:18:01 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 16:37:37 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

static void	destroy_redir_ast_ptr(void *p)
{
	destroy_redir_ast((t_ast *)p);
}

void	destroy_command_ast(t_ast *nnull_ast)
{
	ft_lstclear(&nnull_ast->expr.command.text_list, destroy_block);
	ft_lstclear(&nnull_ast->expr.command.redir_list, destroy_redir_ast_ptr);
}
