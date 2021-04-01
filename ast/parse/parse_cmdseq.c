/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdseq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:23 by lzins             #+#    #+#             */
/*   Updated: 2021/04/02 00:00:16 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_status	parse_cmdseq(t_list **ast_list, t_list *tokens)
{
	t_ast *ast_cmdchain;
	t_status status;

	*ast_list = NULL;
	while (tokens)
	{
		if (parse_cmdchain(&ast_cmdchain, &tokens) != STATUS_OK)
			return (STATUS_ERROR);
		if (!ft_lstadd_back_content(ast_list, ast_cmdchain))
			return (STATUS_ERROR);
		if (is_eof_lst(tokens))
			return (STATUS_OK);
		if (!identify_semicol(&tokens))
		{
			// print_block(block_at(tokens));
			return (unexpected_token_error(tokens));
		}
	}
	return (STATUS_OK);
}
