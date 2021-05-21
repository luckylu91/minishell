/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 10:46:00 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 11:08:15 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// File descriptor of a redir ast
int	redir_fd_at(t_ast *redir_ast)
{
	return (redir_ast->expr.redir.fildes);
}

// Operator of a redir ast
t_block	*redir_op_at(t_ast *redir_ast)
{
	return (redir_ast->expr.redir.redir_op);
}

// File name of a redir ast (list of blocks)
t_list	*redir_fname_at(t_ast *redir_ast)
{
	return (redir_ast->expr.redir.file_name);
}

/*
	Whether a redirection results in ambiguous error after environment
	variables substitution
*/
int	redir_is_ambiguous(t_ast *redir_ast)
{
	return (redir_ast->expr.redir.ambiguous_error);
}
