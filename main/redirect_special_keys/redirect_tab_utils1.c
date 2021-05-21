/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tab_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:14:15 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 16:42:40 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect_tab_utils.h"

int	startswith(char *str, char *prefix)
{
	if (!prefix)
		return (1);
	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

char	last_char(char *str)
{
	if (!*str)
		return ('\0');
	return (str[ft_strlen(str) - 1]);
}

static char	*duplicate_line_until_cursor(t_minishell *ms)
{
	char	*res;

	if (ms->lb->i == 0 || !ms->lb->buffer)
		return (NULL);
	res = ft_calloc(ms->lb->i + 1, sizeof(char));
	ft_strlcpy(res, ms->lb->buffer, ms->lb->i + 1);
	return (res);
}

static t_block	*duplicate_last_block(char *line_until_cursor,
	t_block *last_block)
{
	char	*buffer_end;

	buffer_end = ft_strrchr(line_until_cursor, last_char(last_block->str));
	if (*buffer_end == ' ' && ft_all_in(buffer_end, " "))
		return (create_block(none, ft_strdup("")));
	else if (!ft_all_in(buffer_end + 1, "\'\"\\"))
		return (NULL);
	else
		return (dup_block(last_block));
}

t_block	*valid_last_block(t_minishell *ms)
{
	t_list	*block_lst;
	char	*str_until_cursor;
	t_block	*last_block;

	str_until_cursor = duplicate_line_until_cursor(ms);
	to_block(str_until_cursor, &block_lst);
	if (!block_lst)
		return (NULL);
	last_block = ft_lstlast(block_lst)->content;
	if (!last_block->str)
	{
		ft_lstclear(&block_lst, destroy_block);
		return (NULL);
	}
	last_block = duplicate_last_block(str_until_cursor, last_block);
	ft_lstclear(&block_lst, destroy_block);
	return (last_block);
}
