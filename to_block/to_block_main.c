/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_block_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgallien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:24:39 by hgallien          #+#    #+#             */
/*   Updated: 2021/03/30 11:42:41 by hgallien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
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
t_block		*new_block(char *c, enum flags f)
{
	t_block *b;
	b = malloc(sizeof(t_block*));
	if(!(b))
		return (NULL);
	b->str = ft_strdup(c);
	b->f = f;
	return (b);
}
void		in_quote(char *line, t_var_toblock *var, t_list **temp_l)
{
	var->i = var->i + 1;
	char buffer[10];
	//printf("in auote \n");
	while (line[var->i] != '\'')
	{
		if (line[var->i] == '\0')
		{
			read(STDIN_FILENO, buffer, 10);
		}
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
		//	printf("while in quote i = %i\n",var->i);
	}
	var->i =var->i +1;
}

void	handle_space(t_var_toblock *var, t_list **final_l,t_list **temp_l, char *line)
{
	ft_lstadd_back(final_l, ft_lstnew(new_block(" ", space)));
	while (line[var->i] == ' ')
	{
		var->i = var->i + 1;
	}
}


char 	*list_to_string(t_list *l)
{
	char *str;
	int i;
	t_list *parcour_l;

	i = 0;
	parcour_l = l;	
	str = malloc(sizeof(char) * ft_lstsize(l) + 1);
	while (l != NULL)
	{
		str[i] = *((char*)l->content);
		i++;
		parcour_l = l;
		l = l->next;
		//printf("dqns temp_to final 3\n");
		free(parcour_l);
	}
	str[i] = '\0';
	return (str);
}
void	temp_to_final(t_list **final_l, t_list **temp_l, enum flags f)
{
	char *str;
	t_list *temp_lbis;
	temp_lbis = *temp_l;
	int i;

	//	printf("dqns temp_to final 1\n");
	i = 0;
	str = list_to_string(temp_lbis);
	*temp_l = NULL;
	ft_lstadd_back(final_l, ft_lstnew(new_block(str, f)));
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

void	str_to_list(char *str, t_list **temp_l)
{
	int i;

	i = 0;
	while (str[i])	
	{
		ft_lstadd_back(temp_l, ft_lstnew(&str[i]));
		i++;
	}	

}
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
		ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar_num)));
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

/*void	env_integration(t_list **temp_l, t_list **final_l, char **env)
{
	int i;
	int j;

	i = i;
	j = 0;
	while (env[0][j])
	{
		ft_lstadd_back(temp_l, ft_lstnew(&env[0][j]));
		j++;
	}
	

}*/
void	in_back_slash(char *line, t_var_toblock *var, t_list **final_l, t_list **temp_l)
{
	var->i = var->i + 1;
	if (line[var->i] == '\n' || line[var->i] == '\0')
	{
		//to do
		return ;
	}
	else
	{
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i=var->i + 1;
	}
}


void	in_back_slash_dquote(char *line, t_var_toblock *var, t_list **final_l, t_list **temp_l)
{
	if (line[var->i] == '\'' ||line[var->i] == '$' || line[var->i] == '\"') 
	{
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i +1 ;
	}
	else
	{

		ft_lstadd_back(temp_l, ft_lstnew("\\"));
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i +1 ;
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
	if (ft_isdigit(line[var->i]))
	{
	//	printf(" digit in $ in \" \n");
		ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
		str = list_to_string(env_var);	
		ft_lstadd_back(final_l, ft_lstnew(new_block(str, dollar_num)));
	}
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

void	in_double_quote(char *line, t_var_toblock *var, t_list **final_l, t_list **temp_l)
{
	var->i = var->i + 1;
	//printf("Debut double q %c\n",line[var->i]);
	while (line[var->i] != '\"')
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
	var->i = var->i +1;

	//printf("end dquote c = %c \n", line[var->i]);
}
void	redirection(t_var_toblock *var, char *line, t_list **final_l, t_list **temp_l)
{
	if (*temp_l != NULL)
		temp_to_final( final_l, temp_l, none);
	while (ft_isdigit(line[var->i]))
	{
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
	}
	ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
	temp_to_final(final_l, temp_l, spe);
	var->i = var->i + 1;
}



int		test_redir(char *line, t_var_toblock *var, t_list *temp_l)
{
	int i;

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
			if(line[i] == '>' || line[i] == '<')
				return (1);
		}
	}
	return (0);
}

void	in_tild(char *line, t_var_toblock *var, t_list **final_l, t_list **temp_l)
{
	if (*temp_l != NULL || !(is_separator(&line[var->i + 1])))
	{
		//printf("not tilt c=|%c| \n",line[var->i+1]);
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
	}
	else
	{
		//printf("is tilt\n");
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		temp_to_final(final_l, temp_l, spe);
	}
	var->i = var->i + 1;
}
void 	to_block(char *line, t_list **final_l)
{
	printf("####\n|%s|\n####\n",line);
	
	t_var_toblock var;
	t_list	*temp_l;
	temp_l = NULL;
	*final_l= NULL;
	var.i = 0;
	var.spe = 0;
	var.end_while = 1;
	/*if (line == NULL || ft_all_in(line," "))
	{
		printf("c4est comme moi\n");
		return;
	}*/
	while (var.end_while) 
	{
		//printf("i = %i c = |%c|  end = %i\n",var.i,line[var.i], var.end_while);
		if (is_separator(&line[var.i]))
			handle_separator(&var, line, final_l, &temp_l);
		else if (test_redir(line, &var, temp_l))
			redirection(&var, line, final_l, &temp_l);
		else if (line[var.i] == '\'')
			in_quote(line, &var, &temp_l);
		else if(line[var.i] == '$')
			ft_dollar(&var, line, &temp_l, final_l);
		else if (line[var.i] == '\"')
			in_double_quote(line, &var,final_l, &temp_l);
		else if (line[var.i] == '\\')
			in_back_slash(line, &var, final_l, &temp_l);
		else
		{
			//	printf("ici nothing\n");
			if (line[var.i] == '~')
			{
		//		printf("dans ~\n");
				in_tild(line, &var, final_l, &temp_l); 
			}
			ft_lstadd_back(&temp_l, ft_lstnew(&line[var.i]));
			//	printf("la \n");
			var.i++;
		}		
	}
}
