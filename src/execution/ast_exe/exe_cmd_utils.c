#include "execution.h"

char	*get_char_from_block(t_list *l)
{
	return (((t_block *)(l->content))->str);
}

void	dup_str(t_list *l, char **res, int i)
{
	enum e_flags	f;

	if (l != NULL)
	{
		f = ((t_block *)(l->content))->f;
		if (f == none)
		{
			res[i] = ft_strdup(get_char_from_block(l));
			dup_str(l->next, res, i + 1);
		}
		else
			dup_str(l->next, res, i);
	}
	else
		res[i] = NULL;
}

int	size_list(t_list *l)
{
	if (l == NULL)
		return (0);
	return (size_list(l->next) + 1);
}

char	**from_list_to_str_tab(t_list *l)
{
	int		t;
	char	**res;

	t = size_list(l);
	res = wrap_malloc(sizeof(char *) * (t + 1));
	dup_str(l, res, 0);
	res[t] = NULL;
	return (res);
}

int	is_last(t_list *l, char c, int fildes, fd_err *err)
{
	if (l == NULL)
		return (1);
	if (redir_op_at(l->content)->str[0] == c
		&& redir_fd_at(l->content) == fildes)
		return (0);
	return (is_last(l->next, c, fildes, err));
}
