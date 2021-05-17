#include "to_block.h"


void	in_double_quote(char *line, t_var_toblock *var, t_list **final_l, t_list **temp_l)
{
	var->i = var->i + 1;
	//printf("Debut double q %c\n",line[var->i]);
	while (line[var->i] && line[var->i] != '\"')
	{
		//printf(" debut while \" i = %i c = %c \n", var->i, line[var->i]);
		if (line[var->i] == '$')
		{
			//printf("$ in double  quote\n");
			var->i = var->i + 1;
			ft_dollar_dquote(line, var, final_l, temp_l);
			//printf(" after $ in \" i = %i c= |%c| \n", var->i, line[var->i]);
		}
		else if (line[var->i] == '\\')
		{
			//printf("back slash in dquote i = %i \n",var->i);
			var->i = var->i + 1;
			in_back_slash_dquote(line, var, final_l, temp_l);
		}
		else
		{
			//printf("else double Q c = %c \n", line[var->i]);
			ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
			var->i = var->i + 1;

			//printf("2else double Q c = %c \n", line[var->i]);
		}
	}
	if (line[var->i] == '\"')
		var->i = var->i +1;

	//printf("end dquote c = %c \n", line[var->i]);
}
