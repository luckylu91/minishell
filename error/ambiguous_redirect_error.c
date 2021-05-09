/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:36:25 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 14:28:46 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

static void print_block_error_raw(void *block_ptr)
{
	t_block	*block;

	block = (t_block *)block_ptr;
	if (is_dollar(block))
		ft_putchar_fd('$', STDERR_FILENO);
	ft_putstr_fd(block->str, STDERR_FILENO);
}


int	ambiguous_redirect_error(t_list *redir_blocks)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_lstiter(redir_blocks, NULL, print_block_error_raw);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	ft_lstclear(&redir_blocks, destroy_block);
	return (-1);
}
