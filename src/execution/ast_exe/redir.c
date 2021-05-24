#include "execution.h"

int	in_part(t_list *l, int *res)
{
	int	fd;

	if (((t_ast *)l->content)->expr.redir.redir_op->str[1] == '>')
		fd = open(get_char_from_block((((t_ast *)
							(l->content))
						->expr.redir.file_name)), O_CREAT | O_RDWR | O_APPEND,
				0666);
	else
		fd = open(get_char_from_block((((t_ast *)
							(l->content))->expr.redir.file_name)),
				O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (is_last(l->next, '<', (redir_fd_at(l->content))) == -3)
		return (-3);
	if (is_last(l->next, '>', redir_fd_at(l->content)))
		res[redir_fd_at(l->content)] = fd;
	else
		close(fd);
	return (fd);
}

int	msg_error(t_list *l)
{
	ft_putendl_fd("bash: ", 2);
	ft_putendl_fd(get_char_from_block((((t_ast *)
						(l->content))->expr.redir.file_name)), 2);
	ft_putendl_fd(": No such file or directory ", 2);
	return (-1);
}

int	get_redir_fd(int *res, t_list *l)
{
	int	fd;

	if (l == NULL)
		return (1);
	if ((((t_ast *)(l->content))->expr.redir).redir_op->str[0] == '<')
	{
		fd = open(get_char_from_block((((t_ast *)
							(l->content))->expr.redir.file_name)), O_RDWR);
		if (fd == -1)
			return (msg_error(l));
		if (is_last(l->next, '<', (redir_fd_at(l->content))) == -3)
			return (-3);
		if (is_last(l->next, '<', (redir_fd_at(l->content))))
			res[redir_fd_at(l->content)] = fd;
		else
			close(fd);
	}
	if (((t_ast *)l->content)->expr.redir.redir_op->str[0] == '>')
	{
		fd = in_part(l, res);
		if (fd == -1)
			return (-1);
	}
	return (get_redir_fd(res, l->next));
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
