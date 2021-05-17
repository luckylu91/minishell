#include "to_block.h"

int		is_separator(char *c)
{
	if (c[0] == '|' || c[0] == ' ' || c[0] == ';'  ||c[0] == '\0' || c[0] == '\n')
		return (1);
	return (0);
}	

int		is_separator_for_dollar(char *c)
{
	if (c[0] == '|' || c[0] == ' ' || c[0] == ';'  ||c[0] == '\0' || c[0] == '<')
		return (1);
	if(c[0] == '\'' || c[0] == '\"' || c[0] == '\\' || c[0] == '\n' || c[0] =='>')
		return (1);
	return (0);
}

void	handle_separator(t_var_toblock *var, char *line, t_list **final_l, t_list **temp_l)
{
	//	printf("dans handle sep |%c|\n",line[var->i]);
	if (*temp_l != NULL)
	{
		temp_to_final(final_l, temp_l, none);
	}	
	if(line[var->i] == ' ')
	{
		//	printf("dans handle space\n");
		while (line[var->i] == ' ')
			var->i = var->i + 1;
		//if(line[var->i] != '\n' && line[var->i] != '\0')
		ft_lstadd_back(final_l, ft_lstnew(new_block(" ", space)));
	}
	else if (line[var->i] == ';')
	{
		ft_lstadd_back(final_l, ft_lstnew(new_block(";", spe)));
		var->i = var->i +1;
	}
	else if (line[var->i] == '|') 
	{
		ft_lstadd_back(final_l, ft_lstnew(new_block("|", spe)));
		var->i = var->i +1;
	}
	else if (line[var->i] == '\0') 
	{
		var->end_while = 0;

		//	printf("dans dans == '0' \n");
	}
}
