#include "to_block.h"

void	in_quote(char *line, t_var_toblock *var, t_list **temp_l)
{
	char	buffer[10];

	var->i = var->i + 1;
	while (line[var->i] != '\'')
	{
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
	}
	if (line[var->i] == '\'')
		var->i =var->i +1;
}
