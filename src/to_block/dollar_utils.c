#include "to_block.h"

void	digit_quest(t_var_toblock *var, char *line,
	 t_list **temp_l, t_list **final_l)
{
	if (line[var->i] == '?')
		temp_to_final(final_l, temp_l, dollar);
	else
		temp_to_final(final_l, temp_l, dollar_num);
	var->i = var->i + 1;
}

int	condition(char *line, t_var_toblock *var, t_list **temp_l)
{
	if (line[var->i] == '\'' || line[var->i] == '\"')
		return (1);
	if (line[var->i] == '\\' || line[var->i] == '\0'
		|| line[var->i] == ' ' || line[var->i] == '\n' || line[var->i] == '~')
	{
		ft_lstadd_back(temp_l, ft_lstnew("$"));
		return (1);
	}
	return (0);
}

void 	test_intero(char *line, t_var_toblock *var,
		t_list **temp_l, t_list **final_l)
{
	if (line[var->i] == '?')
		temp_to_final(final_l, temp_l, dollar);
	else
		temp_to_final(final_l, temp_l, dollar_num);
	var->i = var->i + 1;
}
