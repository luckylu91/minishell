#include "to_block.h"


void		in_quote(char *line, t_var_toblock *var, t_list **temp_l)
{
	var->i = var->i + 1;
	char buffer[10];
	//printf("in auote \n");
	while (line[var->i] && line[var->i] != '\'')
	{
		if (line[var->i] == '\0')
		{
			read(STDIN_FILENO, buffer, 10);
		}
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
		//	printf("while in quote i = %i\n",var->i);
	}
	if (line[var->i] == '\'')
		var->i =var->i +1;
}
