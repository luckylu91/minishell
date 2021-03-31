/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdseq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:23 by lzins             #+#    #+#             */
/*   Updated: 2021/03/31 11:55:53 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_status	parse_cmdseq(t_ast **ast, t_list *tokens)
{
	t_ast *ast_cmdchain;
	t_status status;

	*ast = NULL;
	if (!create_ast(ast, binary_expr))
		return (STATUS_ERROR);
	while (tokens)
		if (parse_cmdchain(&ast_cmdchain, &tokens) != STATUS_OK)
			return (STATUS_ERROR);
		if (is_eof_lst(tokens))
			return (STATUS_OK);
		if (!identify_semicol(&tokens))
			return (unexpected_token_error(tokens));
	return (STATUS_OK);
}
