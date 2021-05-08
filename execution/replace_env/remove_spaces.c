#include "execution.h"

static int	lststr_cat_len(t_list *block_lst)
{
	int		n;
	t_block	*block;

	if (!block_lst)
		return (0);
	block = block_at(block_lst);
	if (block->f == space)
		return (0);
	return (ft_strlen(block->str) + lststr_cat_len(block_lst->next));
}

static int	num_none_blocks(t_list *block_lst)
{
	int		n;
	t_block	*block;

	if (!block_lst)
		return (0);
	block = block_at(block_lst);
	if (block->f == space)
		return (0);
	else if (block->f != none || !block->str)
		return (-1);
	n = num_none_blocks(block_lst->next);
	if (n == -1)
		return (-1);
	return (1 + n);
}

static void	lststr_cat(char *str, t_list **block_lst)
{
	t_block	*block;

	if (!*block_lst)
		return ;
	block = block_at(*block_lst);
	if (block->f == space)
		return ;
	str = ft_strcat_and_move(str, block->str);
	*block_lst = (*block_lst)->next;
	lststr_cat(str, block_lst);
}

int	text_to_string(t_list **block_lst, char **str_addr)
{
	int		n;
	size_t	tot_len;

	*str_addr = NULL;
	if (!*block_lst)
		return (1);
	n = num_none_blocks(*block_lst);
	if (n == -1)
	{
		ft_putstr_fd("Error in blocks list detected in "\
			"execution/text_to_string.c\n", STDERR_FILENO);
		return (-1);
	}
	if (n == 0)
		return (1);
	tot_len = lststr_cat_len(*block_lst);
	*str_addr = ft_calloc(tot_len + 1, sizeof(char));
	if (!*str_addr)
		return (-1);
	lststr_cat(*str_addr, block_lst);
	return (1);
}

int	remove_spaces(t_list *block_lst, t_list **new_block_lst)
{
	char	*str;
	int		ret;
	t_block	*new_block;

	*new_block_lst = NULL;
	while (block_lst)
	{
		skip_spaces(&block_lst);
		new_block = ft_calloc(1, sizeof(t_block));
		if (text_to_string(&block_lst, &str) == -1)
		{
			wrap_free(str);
			ft_lstclear(&block_lst, destroy_block);
			return (-1);
		}
		ft_lstadd_back_content(new_block_lst, new_block);
		new_block->f = none;
		new_block->str = str;
	}
	return (1);
}
