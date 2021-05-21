/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:48:34 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 11:08:39 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Text content for a text ast (list of blocks)
t_list	*text_at(t_ast *text_ast)
{
	return (text_ast->expr.text);
}
