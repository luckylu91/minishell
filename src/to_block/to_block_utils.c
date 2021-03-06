#include "to_block.h"

t_block	*new_block(char *c, enum e_flags f)
{
	t_block	*b;

	b = wrap_malloc(sizeof(t_block *));
	if (!(b))
		return (NULL);
	b->str = ft_strdup(c);
	b->f = f;
	return (b);
}

void	handle_space(t_var_toblock *var, t_list **final_l,
		t_list **temp_l, char *line)
{
	(void)temp_l;
	ft_lstadd_back(final_l, ft_lstnew(new_block(" ", space)));
	while (line[var->i] == ' ')
	{
		var->i = var->i + 1;
	}
}

char 	*list_to_string(t_list *l)
{
	char	*str;
	int		i;
	t_list	*parcour_l;

	i = 0;
	parcour_l = l;
	str = wrap_malloc(sizeof(char) * ft_lstsize(l) + 1);
	while (l != NULL)
	{
		str[i] = *((char *)l->content);
		i++;
		parcour_l = l;
		l = l->next;
		wrap_free(parcour_l);
	}
	str[i] = '\0';
	return (str);
}

void	temp_to_final(t_list **final_l, t_list **temp_l, enum e_flags f)
{
	t_list	*temp_lbis;
	int		i;
	t_block	*block;

	temp_lbis = *temp_l;
	i = 0;
	*temp_l = NULL;
	block = ft_calloc(1, sizeof(t_block *));
	block->f = f;
	block->str = list_to_string(temp_lbis);
	ft_lstadd_back(final_l, ft_lstnew(block));
}

void	str_to_list(char *str, t_list **temp_l)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_lstadd_back(temp_l, ft_lstnew(&str[i]));
		i++;
	}	
}
