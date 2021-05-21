#include "to_block.h"

void	in_double_quote(char *line, t_var_toblock *var,
		t_list **final_l, t_list **temp_l)
{
	var->i = var->i + 1;
	while (line[var->i] && line[var->i] != '\"')
	{
		if (line[var->i] == '$')
		{
			var->i = var->i + 1;
			ft_dollar_dquote(line, var, final_l, temp_l);
		}
		else if (line[var->i] == '\\')
		{
			var->i = var->i + 1;
			in_back_slash_dquote(line, var, temp_l);
		}
		else
		{
			ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
			var->i = var->i + 1;
		}
	}
	if (line[var->i] == '\"')
		var->i = var->i + 1;
}
