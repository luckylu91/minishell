/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:21:30 by lzins             #+#    #+#             */
/*   Updated: 2021/05/25 12:36:40 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	replace_env(t_ast *cmdchain_ast, t_minishell *ms)
{
	if (!cmdchain_ast)
		return ;
	if (cmdchain_ast->type == command_expr)
		replace_env_cmd(cmdchain_ast, ms);
	else if (cmdchain_ast->type == binary_expr)
	{
		replace_env(cmdchain_ast->expr.binary.left, ms);
		replace_env(cmdchain_ast->expr.binary.right, ms);
	}
}
