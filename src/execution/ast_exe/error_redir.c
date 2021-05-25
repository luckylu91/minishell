#include "execution.h"

int	set_error_one(t_list *l, fd_err *err)
{
	err->file_name = get_char_from_block((((t_ast *)
					(l->content))->expr.redir.file_name));
	return (-1);
}

int	set_error_two(t_list *l, fd_err *err)
{
	err->ambi = (((t_ast *)(l->content))->expr.redir).name_before_replace;
	return (-2);
}

int	set_error_three(t_list *l, fd_err *err)
{
	if(redir_fd_at(l->content) == -1)
		err->descri = -1;
	else
		err->descri = redir_fd_at(l->content);
	return (-3);
}
