/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:36:25 by lzins             #+#    #+#             */
/*   Updated: 2021/04/21 14:40:57 by lzins            ###   ########lyon.fr   */
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

// static void *block_to_str(void *block_ptr)
// {
// 	t_block	*block;
// 	char	*block_str;
// 	char	*str;
// 	size_t	size;
// 	int		i;

// 	size = 0;
// 	block = (t_block *)block_ptr;
// 	if (is_dollar(block))
// 		size++;
// 	if (!block->str)
// 		block_str = "";
// 	else
// 		block_str = block->str;
// 	size += ft_strlen(block_str);
// 	str = ft_calloc(size + 1, sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	if (is_dollar(block))
// 		str[i++] = '$';
// 	ft_strcat(str + i, block_str);
// 	return (str);
// }

int	ambiguous_redirect_error(t_ast *redir_ast)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_lstiter(redir_ast->expr.redir.file_name, print_block_error_raw);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	return (-1);
}
