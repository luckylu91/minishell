/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tab_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:17:08 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 11:32:08 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect_tab_utils.h"

void	show_matching_files(t_list *files, t_minishell *ms)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_lstiter(files, NULL, ft_putendl_fd);
	show_prompt(ms);
	ft_putstr_fd(ms->lb->buffer, STDOUT_FILENO);
}

void	get_contextual_tabinfo(t_tabinfo *tabinfo, t_minishell *ms)
{
	t_block	*last_block;
	char	*cwd;
	char	*str_path;

	last_block = valid_last_block(ms);
	if (!last_block)
	{
		tabinfo->do_nothing = 1;
		destroy_block(last_block);
		return ;
	}
	cwd = our_getcwd();
	separate_last_slash(last_block->str, &str_path,
		&tabinfo->str_to_complete);
	if (is_dir(NULL, str_path))
		tabinfo->basedir = ft_strdup(str_path);
	else if (str_path)
		tabinfo->do_nothing = 1;
	else
		tabinfo->basedir = ft_strdup(cwd);
	wrap_free(cwd);
	wrap_free(str_path);
	destroy_block(last_block);
}

void	common_prefix_fun(char *str, char **prefix)
{
	int	i;

	if (!*prefix)
		*prefix = ft_strdup(str);
	else
	{
		i = 0;
		while ((*prefix)[i] && str[i] == (*prefix)[i])
			i++;
		(*prefix)[i] = '\0';
	}
}
