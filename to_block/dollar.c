#include "to_block.h"

void	ft_dollar(t_var_toblock *var, char *line, t_list **temp_l, t_list **final_l)
{
	//printf("start $\n");
	t_list *env_var;
	char *str;
	var->i = var->i + 1;
	env_var = NULL;
	if (line[var->i] == '\'' || line[var->i] == '\"')
	{
		return ;
	}
	if (line[var->i] == '\\' || line[var->i] == '\0' || line[var->i] == ' ' || line[var->i] == '\n' || line[var->i] == '~')
	{
		ft_lstadd_back(temp_l, ft_lstnew("$"));	
		return ;
	}
	if (ft_isdigit(line[var->i]) || line[var->i] == '?')
	{
		ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
		str = list_to_string(env_var);	
		if (line[var->i] == '?')
			ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar)));
		else
			ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar_num)));
		var->i = var->i + 1;
	}
	else
	{

		//	printf(" else$\n");
		if (*temp_l != NULL)
			temp_to_final(final_l, temp_l, none);


		while (ft_isalnum(line[var->i]) || line[var->i] =='_')
		{	
			ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
			var->i = var->i + 1;
		}
		str = list_to_string(env_var);
		//		printf("DANS $ str = %s\n",str);
		//ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar)));
		ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar)));
	}
}
void	ft_dollar_dquote(char *line, t_var_toblock *var, t_list **final_l, t_list **temp_l)
{
	//printf("start $\n");
	t_list *env_var;
	char *str;
	env_var = NULL;
	if (line[var->i] == '\\') 
	{
		//	printf(" \\ in $ in \" \n");
		ft_lstadd_back(temp_l, ft_lstnew("$"));	
		var->i = var->i + 1;
		in_back_slash_dquote(line, var, final_l, temp_l);
		return ;
	}
	if (line[var->i] == '~')
	{
		ft_lstadd_back(temp_l, ft_lstnew("$"));	
		return ;
	}
	if (ft_isdigit(line[var->i]) || line[var->i] == '?')
	{
		ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
		str = list_to_string(env_var);	
		if (line[var->i] == '?')
			ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar)));
		else
			ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar_num)));
		var->i = var->i + 1;
	}
/*	if (ft_isdigit(line[var->i]))
	{
		//	printf(" digit in $ in \" \n");
		ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
		str = list_to_string(env_var);	
		ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar_num)));
	}*/
	else
	{
		if (*temp_l != NULL)
			temp_to_final(final_l, temp_l, none);
		//printf(" else$\n");
		while (ft_isalnum(line[var->i]) ||line[var->i] == '_')
		{	
			//printf(" while in $ in \" c = %c \n", line[var->i]);
			ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
			var->i = var->i + 1;
		}
		str = list_to_string(env_var);
		//	printf("DANS $ str = %s\n",str);
		ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar_dquote)));
		//printf("end $ c = %c \n", line[var->i]);
	}
}

