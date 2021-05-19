/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tab_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:14:15 by lzins             #+#    #+#             */
/*   Updated: 2021/05/19 15:04:06 by lzins            ###   ########lyon.fr   */
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

t_block	*valid_last_block(t_minishell *ms)
{
	t_list			*block_lst;
	t_linebuffer	*lb;
	t_block			*last_block;
	char			*buffer_end;

	lb = ms->lb;
	if (!lb->buffer)
		return (NULL);
	to_block(lb->buffer, &block_lst);
	if (!block_lst)
		return (NULL);
	last_block = ft_lstlast(block_lst)->content;
	if (!last_block->str)
	{
		ft_lstclear(&block_lst, destroy_block);
		return (NULL);
	}
	buffer_end = ft_strrchr(lb->buffer, last_char(last_block->str));
	if (*buffer_end == ' ' && ft_all_in(buffer_end, " "))
		last_block = create_block(none, ft_strdup(""));
	else if (!ft_all_in(buffer_end + 1, "\'\"\\"))
		last_block = NULL;
	else
		last_block = dup_block(last_block);
	ft_lstclear(&block_lst, destroy_block);
	return (last_block);
}

void	show_matching_files(t_list *files, t_minishell *ms)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_lstiter(files, NULL, ft_putendl_fd);
	show_prompt(ms);
	ft_putstr_fd( ms->lb->buffer,  STDOUT_FILENO);
}

void	separate_last_slash(char *str, char **str_path, char **str_end)
{
	int	i_sep;

	*str_path = ft_strdup(str);
	*str_end = ft_strrchr(*str_path, '/');
	if (!*str_end)
	{
		*str_end = *str_path;
		*str_path = NULL;
	}
	else
	{
		*str_end = ft_strdup((*str_end) + 1);
		i_sep = ft_strlen(*str_path) - ft_strlen(*str_end);
		(*str_path)[i_sep] = '\0';
	}
}
