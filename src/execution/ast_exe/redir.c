#include "execution.h"

int	in_part(t_list *l, int *res, t_fd_err *err)
{
	int	fd;

	if (overflow_fd(l, err))
		return (-3);
	if (redir_op_str_at(l->content)[1] == '>')
		fd = open(block_str_at(redir_fname_at(l->content)),
				O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		fd = open(block_str_at(redir_fname_at(l->content)),
				O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		return (set_error_one(l, err));
	if (res[redir_fd_at(l->content)] >= 0)
		close(res[redir_fd_at(l->content)]);
	res[redir_fd_at(l->content)] = fd;
	return (fd);
}

int	get_redir_fd(int *res, t_list *l, t_fd_err *err)
{
	int	fd;

	if (l == NULL)
		return (1);
	if (overflow_fd(l, err))
		return (-3);
	if (redir_is_ambiguous(l->content))
		return (set_error_two(l, err));
	if (redir_op_str_at(l->content)[0] == '<')
	{
		fd = open(block_str_at(redir_fname_at(l->content)), O_RDWR);
		if (fd == -1)
			return (set_error_one(l, err));
		if (res[redir_fd_at(l->content)] >= 0)
			close(res[redir_fd_at(l->content)]);
		res[redir_fd_at(l->content)] = fd;
	}
	if (redir_op_str_at(l->content)[0] == '>')
	{
		fd = in_part(l, res, err);
		if (fd < 0)
			return (fd);
	}
	return (get_redir_fd(res, l->next, err));
}

void	setup_all_fd(int *fd)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (fd[i] >= 0)
			dup2(fd[i], i);
		i++;
	}
}

void	close_all_fd(int *fd)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (fd[i] >= 0)
			close(fd[i]);
		i++;
	}
}
/* int	check_redir(t_both_fd *fd) */
/* { */
/* if (fd->in != NULL) */
/* { */
/* fd->int_in = open(get_char_from_block(fd->in->expr.redir.file_name), */
/* O_RDWR, 0666); */
/* if (fd->int_in == -1) */
/* return (1); */
/* } */
/* if (fd->out != NULL) */
/* { */
/* if (fd->out->expr.redir.redir_op->str[1] == '>') */
/* fd->int_out = open(get_char_from_block( */
/* fd->out->expr.redir.file_name), */
/* O_WRONLY | O_APPEND, 0666); */
/* else */
/* fd->int_out = open(get_char_from_block( */
/* fd->out->expr.redir.file_name), */
/* O_WRONLY | O_TRUNC, 0666); */
/* if (fd->int_out == -1) */
/* return (1); */
/* } */
/* return (0); */
/* } */
