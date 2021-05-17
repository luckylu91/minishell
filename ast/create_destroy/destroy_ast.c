/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:10:43 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 14:19:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	destroy_ast(t_ast **ast)
{
	if (!*ast)
		return ;
	(*ast)->destruct(*ast);
	*ast = NULL;
}

static void	destroy_ast_ptr(void *ast)
{
	destroy_ast((t_ast **)&ast);
}

void	destroy_ast_list(t_list **ast_lst)
{
	ft_lstclear(ast_lst, destroy_ast_ptr);
}
