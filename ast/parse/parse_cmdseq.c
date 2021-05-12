/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdseq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:23 by lzins             #+#    #+#             */
/*   Updated: 2021/05/12 17:23:53 by lzins            ###   ########lyon.fr   */
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
		if (parse_cmdchain(&ast_cmdchain, &tokens) == STATUS_ERROR)
			return (STATUS_ERROR);
		ft_lstadd_back_content(ast_list, ast_cmdchain);
		if (is_eof_lst(tokens))
			return (STATUS_OK);
		if ((is_semicol_lst(tokens) && !ast_cmdchain) || !is_semicol_lst(tokens))
			return (unexpected_token_error(tokens));
		tokens = tokens->next;
	}
	return (STATUS_OK);
}
