/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_special_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:03 by lzins             #+#    #+#             */
/*   Updated: 2021/05/09 16:37:45 by lzins            ###   ########lyon.fr   */
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

static void	strlen_max(void *str, void *max)
{
	int	len;

	len = ft_strlen(str);
	if (len > *(int *)max)
		*(int *)max = len;
}

static int	startswith(char *str, char *prefix)
{
	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

static char	last_char(char *str)
{
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
	buffer_end = ft_strrchr(lb->buffer, last_char(last_block->str)) + 1;
	if (!ft_all_in(buffer_end, "\'\"\\"))
		last_block = NULL;
	else
		last_block = dup_block(last_block);
	ft_lstclear(&block_lst, destroy_block);
	return (last_block);
}

void	redirect_tab(void)
{
	t_list	*files;
	char *cwd;
	char *basedir;
	// int max_len;
	t_block *last_block;
	int num_files_found;
	char *str_path_part;
	char *str_to_complete;
	char *last_slash;
	int i_sep;

	last_block = valid_last_block();
	if (!last_block)
	{
		// TODO
		printf("\nTab intent with no word\n");
		return ;
	}
	
	cwd = our_getcwd();
	str_path_part = ft_strdup(last_block->str);
	str_to_complete = ft_strrchr(str_path_part, '/');
	if (!str_to_complete)
	{
		str_to_complete = str_path_part;
		str_path_part = NULL;
	}
	else
	{
		str_to_complete = ft_strdup(str_to_complete + 1);
		i_sep = ft_strlen(str_path_part) - ft_strlen(str_to_complete);
		str_path_part[i_sep] = '\0';
	}
	if (is_dir(cwd, str_path_part))
		basedir = pathjoin(cwd, str_path_part);
	else
		basedir = ft_strdup(cwd);
	wrap_free(cwd);
		
	list_dir(basedir, &files);
	// max_len = -1;
	// ft_lstiter(files, &max_len, strlen_max);
	// printf("max_len : %d\n", max_len);
	ft_lstfilter(
		&files,
		last_block->str,
		(t_bool_fun)startswith,
		wrap_free
	);
	num_files_found = ft_lstsize(files);
	if (num_files_found == 1)
	{
		int		i = ft_strlen(last_block->str);
		char	*fname = files->content;
		int		fname_is_dir;
		char	end_char;
		
		fname_is_dir = is_dir(basedir, fname);
		if (i == ft_strlen(fname))
		{
			// TODO
			printf("Tab indent with no word\n");
			return ;
			
		}
		while (fname[i])
		{
			linebuffer_add_insert(fname[i]);
			ft_putchar_fd(fname[i++], g_global_var.fd_out);
		}
		if (fname_is_dir)
			end_char = '/';
		else
			end_char = ' ';
		linebuffer_add_insert(end_char);
		ft_putchar_fd(end_char, g_global_var.fd_out);
	}
	else if (num_files_found > 1)
	{
		ft_putchar_fd('\n', g_global_var.fd_out);
		ft_lstiter(files, NULL, ft_putendl_fd);
		show_prompt();
		ft_putstr_fd(g_global_var.lb->buffer, g_global_var.fd_out);
	}
	destroy_block(last_block);
	ft_lstclear(&files, wrap_free);
}
