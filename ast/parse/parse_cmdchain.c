/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdchain.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:27 by lzins             #+#    #+#             */
/*   Updated: 2021/05/04 16:27:13 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_status	parse_cmdchain(t_ast **cmdchain_ast, t_list **tokens)
{
	t_ast *cmd_ast;
	t_status status;
	t_block *chainop;

	*cmdchain_ast = NULL;
	status = STATUS_OK;
	chainop = NULL;
	while (status == STATUS_OK)
	{
		status = parse_cmd(&cmd_ast, tokens);
		if (!cmd_ast || status == STATUS_ERROR)
			break ;
		add_cmd_tochain(cmdchain_ast, cmd_ast, chainop);
		if (is_semicol_lst(*tokens))
			return (STATUS_OK);
		if (!is_chainop_lst(*tokens))
			break ;
		chainop = dup_block(block_at(*tokens));
		*tokens = ft_lststep(*tokens, 1);
	}
	return (status);
}
