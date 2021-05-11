/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_special_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:03 by lzins             #+#    #+#             */
/*   Updated: 2021/05/11 14:21:48 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_up_down_arrow(int c)
{
	char *c_chars;

	c_chars = (char*)&c;
	return (ft_strncmp(c_chars, "\x1b[", 2) == 0
			&& (c_chars[2] == 'A' || c_chars[2] == 'B'));
}

int		is_left_right_arrow(int c)
{
	char *c_chars;

	c_chars = (char*)&c;
	return (ft_strncmp(c_chars, "\x1b[", 2) == 0
			&& (c_chars[2] == 'C' || c_chars[2] == 'D'));
}

void	clear_current_line(t_hist *h, int fd_out)
{
	int				len_screen;
	int				k;
	t_linebuffer	*lb;
	char			**tc;

	lb = g_global_var.lb;
	tc = g_global_var.termcaps;
	if (!lb->buffer)
		return ;
	while (lb->i < lb->i_max)
	{
		tputs(tparm(tc[MOVE_RIGHT], 1), 1, ft_putchar);
		lb->i++;
	}
	len_screen = ft_strlen(lb->buffer);
	tputs(tparm(tc[MOVE_LEFT], len_screen), 1, ft_putchar);
	k = -1;
	while (++k < len_screen)
		tputs(tc[DELETE_CHAR], 1, ft_putchar);
}

void	redirect_up_down(char* str)
{
	char			*line;
	int				up_pressed;
	t_linebuffer	*lb;
	char			**tc;
	t_hist			*h;
	int				fd_out;

	lb = g_global_var.lb;
	tc = g_global_var.termcaps;
	h = g_global_var.h;
	fd_out = g_global_var.fd_out;
	up_pressed = (str[2] == 'A');
	if ((h->position_state == BOTTOM && !up_pressed) || !h->hlines)
		return ;
	if (up_pressed)
		move_hist(h, 1);
	else
		move_hist(h, -1);
	clear_current_line(h, fd_out);
	set_linebuffer_to(get_hist_line(h));
	if (lb->buffer)
		ft_putstr_fd(lb->buffer, fd_out);
	// put_current_line(lb, h, fd_out);
	// printf("\nCurrent hist line = '%s'\n", get_hist_line(h));
}

int	redirect_left_right(char* str)
{
	int				left_pressed;
	t_linebuffer	*lb;
	char			**tc;

	lb = g_global_var.lb;
	tc = g_global_var.termcaps;
	left_pressed = (str[2] == 'D');
	if (left_pressed && lb->i > 0)
	{
		tputs(tparm(tc[MOVE_LEFT], 1), 1, ft_putchar);
		lb->i--;
	}
	else if (!left_pressed && lb->i < lb->i_max)
	{
		tputs(tparm(tc[MOVE_RIGHT], 1), 1, ft_putchar);
		lb->i++;
	}
	return (1);
}

// static void	strlen_max(void *str, void *max)
// {
// 	int	len;

// 	len = ft_strlen(str);
// 	if (len > *(int *)max)
// 		*(int *)max = len;
// }

static int	startswith(char *str, char *prefix)
{
	if (!prefix)
		return (1);
	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

static char	last_char(char *str)
{
	if (!*str)
		return ('\0');
	return (str[ft_strlen(str) - 1]);
}

static t_block	*valid_last_block(void)
{
	t_list			*block_lst;
	t_linebuffer	*lb;
	t_block			*last_block;
	char			*buffer_end;

	lb = g_global_var.lb;
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

static void	show_matching_files(t_list *files)
{
	ft_putchar_fd('\n', g_global_var.fd_out);
	ft_lstiter(files, NULL, ft_putendl_fd);
	show_prompt();
	ft_putstr_fd(g_global_var.lb->buffer, g_global_var.fd_out);
}

static void	separate_last_slash(char *str, char **str_path, char **str_end)
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

static void	get_contextual_tabinfo(t_tabinfo *tabinfo)
{
	t_block	*last_block;
	char	*cwd;
	char	*str_path;

	last_block = valid_last_block();
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

static void common_prefix_fun(char *str, char **prefix)
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

void	redirect_tab(void)
{
	t_list	*files;
	int num_files_found;
	t_tabinfo	tabinfo;

	get_contextual_tabinfo(&tabinfo);
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
			linebuffer_add_insert(fname[i]);
			ft_putchar_fd(fname[i++], g_global_var.fd_out);
		}
		if (is_dir(tabinfo.basedir, fname))
			end_char = '/';
		else
			end_char = ' ';
		linebuffer_add_insert(end_char);
		ft_putchar_fd(end_char, g_global_var.fd_out);
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
			show_matching_files(files);
		else
		{
			// complete(fname, i, common_prefix)
			while (i < j)
			{
				linebuffer_add_insert(common_prefix[i]);
				ft_putchar_fd(common_prefix[i++], g_global_var.fd_out);
			}
		}
	}
	ft_lstclear(&files, wrap_free);
}
