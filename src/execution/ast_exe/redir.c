#include "execution.h"

int	in_part(t_list *l, t_both_fd *res)
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
				O_CREAT | O_RDWR, 0666);
	if (is_last(l->next, '>'))
		res->out = l->content;
	else
		write(fd, "\0", 1);
	return (fd);
}

int	get_redir_fd(t_both_fd *res, t_list *l)
{
	int	fd;

	if (l == NULL)
		return (1);
	if ((((t_ast *)(l->content))->expr.redir).redir_op->str[0] == '<')
	{
		fd = open(get_char_from_block((((t_ast *)
							(l->content))->expr.redir.file_name)), O_RDWR);
		if (fd == -1)
			return (-1);
		close(fd);
		if (is_last(l->next, '<'))
			res->in = l->content;
	}
	if (((t_ast *)l->content)->expr.redir.redir_op->str[0] == '>')
	{
		fd = in_part(l, res);
		if (fd == -1)
			return (-1);
		close(fd);
	}
	return (get_redir_fd(res, l->next));
}

int	check_redir(t_both_fd *fd)
{
	if (fd->in != NULL)
	{
		fd->int_in = open(get_char_from_block(fd->in->expr.redir.file_name),
				O_RDWR, 0666);
		if (fd->int_in == -1)
			return (1);
	}
	if (fd->out != NULL)
	{
		if (fd->out->expr.redir.redir_op->str[1] == '>')
			fd->int_out = open(get_char_from_block(
						fd->out->expr.redir.file_name),
					O_WRONLY | O_APPEND, 0666);
		else
			fd->int_out = open(get_char_from_block(
						fd->out->expr.redir.file_name),
					O_WRONLY | O_TRUNC, 0666);
		if (fd->int_out == -1)
			return (1);
	}
	return (0);
}
