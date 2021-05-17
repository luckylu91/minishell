/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:48:18 by lzins             #+#    #+#             */
/*   Updated: 2021/03/31 12:00:34 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

void	skip_spaces(t_list **tokens)
{
	if (!*tokens || !is_space(block_at(*tokens)))
		return ;
	*tokens = (*tokens)->next;
	skip_spaces(tokens);
}
