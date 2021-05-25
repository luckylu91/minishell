#include "to_block.h"

void	in_quote(char *line, t_var_toblock *var, t_list **final_l,
	t_list **temp_l)
{
	var->i = var->i + 1;
	while (line[var->i] != '\'')
	{
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
	}
	if (line[var->i] == '\'')
	{
		if (*temp_l == NULL)
			ft_lstadd_back(final_l, ft_lstnew(new_block("", none)));
		var->i = var->i + 1;
	}
}
