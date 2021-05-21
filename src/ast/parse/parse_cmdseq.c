/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdseq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:23 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 11:42:19 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_status	parse_cmdseq(t_list **ast_list, t_list *tokens)
{
	t_ast		*ast_cmdchain;
	t_status	status;

	*ast_list = NULL;
	status = STATUS_OK;
	while (tokens)
	{
		status = parse_cmdchain(&ast_cmdchain, &tokens);
		if (status == STATUS_ERROR)
			break ;
		ft_lstadd_back_content(ast_list, ast_cmdchain);
		if (is_eof_lst(tokens))
			break ;
		if ((is_semicol_lst(tokens) && !ast_cmdchain)
			|| !is_semicol_lst(tokens))
		{
			status = unexpected_token_error(tokens);
			break ;
		}
		tokens = tokens->next;
	}
	if (status == STATUS_ERROR)
		destroy_ast_list(ast_list);
	return (status);
}
