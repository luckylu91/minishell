#include "to_block.h"

void	redirection(t_var_toblock *var, char *line,
		t_list **final_l, t_list **temp_l)
{
	if (*temp_l != NULL)
		temp_to_final(final_l, temp_l, none);
	while (ft_isdigit(line[var->i]))
	{
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
	}
	ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
	if (line[var->i] == '>' && line[var->i + 1] == '>')
	{
		var->i = var->i + 1;
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
	}
	temp_to_final(final_l, temp_l, spe);
	var->i = var->i + 1;
}

int	test_redir(char *line, t_var_toblock *var, t_list *temp_l)
{
	int	i;

	i = var->i;
	if (line[var->i] == '>' || line[var->i] == '<')
		return (1);
	if (temp_l == NULL)
	{
		if (ft_isdigit(line[i]))
		{
			while (ft_isdigit(line[i]))
			{
				i++;
			}
			if (line[i] == '>' || line[i] == '<')
				return (1);
		}
	}
	return (0);
}
