/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_at.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:25:18 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 13:26:44 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_list	*text_at(t_ast *text_ast)
{
	if (!text_ast || text_ast->type != text_expr)
		return (NULL);
	return (text_ast->expr.text);
}
