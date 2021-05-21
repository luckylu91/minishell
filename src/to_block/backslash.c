#include "to_block.h"

void	in_back_slash(char *line, t_var_toblock *var,
		 t_list **temp_l)
{
	var->i = var->i + 1;
	ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
	var->i = var->i + 1;
}

void	in_back_slash_dquote(char *line,
		t_var_toblock *var, t_list **temp_l)
{
	if (line[var->i] == '\'' || line[var->i] == '$' || line[var->i] == '\"')
	{
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
	}
	else
	{
		ft_lstadd_back(temp_l, ft_lstnew("\\"));
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
	}
}
