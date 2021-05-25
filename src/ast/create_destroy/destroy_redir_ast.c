/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_redir_ast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:18:12 by lzins             #+#    #+#             */
/*   Updated: 2021/05/25 11:58:19 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	destroy_redir_ast(t_ast *nnull_ast)
{
	destroy_block(nnull_ast->expr.redir.redir_op);
	ft_lstclear(&nnull_ast->expr.redir.file_name, destroy_block);
	wrap_free(nnull_ast->expr.redir.name_before_replace);
}
