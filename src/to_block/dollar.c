#include "to_block.h"

void	ft_dollar(t_var_toblock *var, char *line,
		t_list **temp_l, t_list **final_l)
{
	t_list	*env_var;
	char	*str;

	var->i = var->i + 1;
	env_var = NULL;
	if (condition(line, var, temp_l))
		return ;
	if (ft_isdigit(line[var->i]) || line[var->i] == '?')
	{
		ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
		str = list_to_string(env_var);
		digit_quest(var, line, str, final_l);
	}
	else
	{
		if (*temp_l != NULL)
			temp_to_final(final_l, temp_l, none);
		while (ft_isalnum(line[var->i]) || line[var->i] == '_')
		{	
			ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
			var->i = var->i + 1;
		}
		str = list_to_string(env_var);
		ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar)));
	}
}

void	ft_dollar_dquote_bis(char *line, t_var_toblock *var,
		t_list **final_l, t_list **temp_l)
{
	t_list	*env_var;
	char	*str;

	env_var = NULL;
	if (ft_isdigit(line[var->i]) || line[var->i] == '?')
	{
		ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
		str = list_to_string(env_var);
		test_intero(line, var, final_l, str);
		var->i = var->i + 1;
	}
	else
	{
		if (*temp_l != NULL)
			temp_to_final(final_l, temp_l, none);
		while (ft_isalnum(line[var->i]) || line[var->i] == '_')
		{	
			ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
			var->i = var->i + 1;
		}
		str = list_to_string(env_var);
		ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar_dquote)));
	}
}

void	ft_dollar_dquote(char *line, t_var_toblock *var,
		t_list **final_l, t_list **temp_l)
{
	if (line[var->i] == '\\')
	{
		ft_lstadd_back(temp_l, ft_lstnew("$"));
		var->i = var->i + 1;
		in_back_slash_dquote(line, var, temp_l);
		return ;
	}
	if (line[var->i] == '~')
	{
		ft_lstadd_back(temp_l, ft_lstnew("$"));
		return ;
	}
	ft_dollar_dquote_bis(line, var, final_l, temp_l);
}
