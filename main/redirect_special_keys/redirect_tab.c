/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:03 by lzins             #+#    #+#             */
/*   Updated: 2021/05/19 11:32:56 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect_tab_utils.h"

void	redirect_tab(t_minishell *ms)
{
	t_list	*files;
	int num_files_found;
	t_tabinfo	tabinfo;

	get_contextual_tabinfo(&tabinfo, ms);
	if (tabinfo.do_nothing)
		return ;
	list_dir(tabinfo.basedir, &files);
	ft_lstfilter(&files, tabinfo.str_to_complete, (t_bool_fun)startswith,
			wrap_free);
	num_files_found = ft_lstsize(files);
	if (num_files_found == 1)
	{
		int		i = ft_strlen(tabinfo.str_to_complete);
		char	*fname = files->content;
		// to_write: files->content
		char	end_char;
		
		// complete(fname, i, files->content)
		while (fname[i])
		{
			linebuffer_add_insert(fname[i], ms);
			ft_putchar_fd(fname[i++], STDOUT_FILENO);
		}
		if (is_dir(tabinfo.basedir, fname))
			end_char = '/';
		else
			end_char = ' ';
		linebuffer_add_insert(end_char, ms);
		ft_putchar_fd(end_char, STDOUT_FILENO);
	}
	else if (num_files_found > 1)
	{
		char	*common_prefix;
		// to_write: common_prefix
		int		common_prefix_len;
		int		i;
		int		j;

		common_prefix = NULL;
		ft_lstiter(files, &common_prefix, (t_fun)common_prefix_fun);
		common_prefix_len = ft_strlen(common_prefix);
		i = ft_strlen(tabinfo.str_to_complete);
		j = ft_strlen(common_prefix);
		if (i == j)
			show_matching_files(files, ms);
		else
		{
			while (i < j)
			{
				linebuffer_add_insert(common_prefix[i], ms);
				ft_putchar_fd(common_prefix[i++], STDOUT_FILENO);
			}
		}
	}
	ft_lstclear(&files, wrap_free);
}
