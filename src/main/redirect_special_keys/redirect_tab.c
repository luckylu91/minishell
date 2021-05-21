/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:03 by lzins             #+#    #+#             */
/*   Updated: 2021/05/20 15:03:35 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect_tab_utils.h"

static void	complete_one_found(t_tabinfo *tabinfo, char *fname_found,
	t_minishell *ms)
{
	int		i;
	char	end_char;

	i = ft_strlen(tabinfo->str_to_complete);
	while (fname_found[i])
	{
		process_printable(fname_found[i], ms);
		i++;
	}
	if (is_dir(tabinfo->basedir, fname_found))
	{
		end_char = '/';
		process_printable('/', ms);
	}
	else
	{
		end_char = ' ';
		if (ms->lb->i == ms->lb->i_max)
			process_printable(' ', ms);
	}
}

static void	complete_several_found(t_tabinfo *tabinfo, t_list *files_found,
	t_minishell *ms)
{
	char	*common_prefix;
	int		common_prefix_len;
	int		i;
	int		j;

	common_prefix = NULL;
	ft_lstiter(files_found, &common_prefix, (t_fun)common_prefix_fun);
	common_prefix_len = ft_strlen(common_prefix);
	i = ft_strlen(tabinfo->str_to_complete);
	j = ft_strlen(common_prefix);
	if (i == j)
		show_matching_files(files_found, ms);
	else
	{
		while (i < j)
		{
			process_printable(common_prefix[i], ms);
			i++;
		}
	}
}

void	redirect_tab(t_minishell *ms)
{
	t_list		*files;
	int			num_files_found;
	t_tabinfo	tabinfo;

	get_contextual_tabinfo(&tabinfo, ms);
	if (tabinfo.do_nothing)
		return ;
	list_dir(tabinfo.basedir, &files);
	ft_lstfilter(&files, tabinfo.str_to_complete, (t_bool_fun)startswith,
		wrap_free);
	num_files_found = ft_lstsize(files);
	if (num_files_found == 1)
		complete_one_found(&tabinfo, files->content, ms);
	else if (num_files_found > 1)
		complete_several_found(&tabinfo, files, ms);
	ft_lstclear(&files, wrap_free);
}
