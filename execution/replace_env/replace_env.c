/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:21:30 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 14:27:41 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	replace_env(t_ast *cmdchain_ast, t_minishell *ms)
{
	if (!cmdchain_ast)
		return (1);
	if (cmdchain_ast->type == command_expr)
	{
		if (replace_env_cmd(cmdchain_ast, ms) < 0)
			return (-1);
	}
	else if (cmdchain_ast->type == binary_expr)
	{
		if (replace_env(cmdchain_ast->expr.binary.left, ms) < 0)
			return (-1);
		if (replace_env(cmdchain_ast->expr.binary.right, ms) < 0)
			return (-1);
	}
	return (1);
}
