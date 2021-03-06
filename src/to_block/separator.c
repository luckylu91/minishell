#include "to_block.h"

int	is_separator(char *c)
{
	if (c[0] == '|' || c[0] == ' ' || c[0] == ';' || c[0] == '\0' || c[0] == '\n')
		return (1);
	return (0);
}	

int	is_separator_for_dollar(char *c)
{
	if (c[0] == '|' || c[0] == ' ' || c[0] == ';' || c[0] == '\0' || c[0] == '<')
		return (1);
	if (c[0] == '\'' || c[0] == '\"' || c[0] == '\\' || c[0] == '\n' || c[0] == '>')
		return (1);
	return (0);
}

static void	separator_temp_l_non_empty(t_var_toblock *var,
	t_list **final_l, t_list **temp_l)
{
	if (*temp_l != NULL)
	{
		if (var->tilde == 1)
		{
			temp_to_final(final_l, temp_l, tilde);
			var->tilde = 0;
		}	
		else
			temp_to_final(final_l, temp_l, none);
	}
}

void	handle_separator(t_var_toblock *var, char *line,
		t_list **final_l, t_list **temp_l)
{
	separator_temp_l_non_empty(var, final_l, temp_l);
	if (line[var->i] == ' ')
	{
		while (line[var->i] == ' ')
			var->i = var->i + 1;
		ft_lstadd_back(final_l, ft_lstnew(new_block(" ", space)));
	}
	else if (line[var->i] == ';')
	{
		ft_lstadd_back(final_l, ft_lstnew(new_block(";", spe)));
		var->i = var->i + 1;
	}
	else if (line[var->i] == '|')
	{
		ft_lstadd_back(final_l, ft_lstnew(new_block("|", spe)));
		var->i = var->i + 1;
	}
	else if (line[var->i] == '\0')
		var->end_while = 0;
}
