/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_block_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgallien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:24:39 by hgallien          #+#    #+#             */
/*   Updated: 2021/03/25 17:32:16 by hgallien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "to_block.h"
int		is_separator(char *c)
{
	if (c[0] == '|' || c[0] == ' ' || c[0] == ';'  ||c[0] == '\0')
		return (1);
	return (0);
}	
int		is_separator_for_dollar(char *c)
{
	if (c[0] == '|' || c[0] == ' ' || c[0] == ';'  ||c[0] == '\0')
		return (1);
	if(c[0] == '\'' || c[0] == '\"' || c[0] == '\\')
		return (1);
	return (0);
}
t_block		*new_block(char *c, enum flags f)
{
	t_block *b;
	b = malloc(sizeof(t_block*));
	if(!(b))
		return (NULL);
	b->str = c;
	b->f = f;
	return (b);
}
void		in_quote(char *line, t_var_toblock *var, t_list **temp_l)
{
	var->i = var->i + 1;
	char buffer[10];
	printf("in auote \n");
	while (line[var->i] != '\'')
	{
		if (line[var->i] == '\0')
		{
			read(STDIN_FILENO, buffer, 10);
		}
		ft_lstadd_back(temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
		printf("while in quote i = %i\n",var->i);
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
	printf("dqns temp_to final 3\n");
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

	printf("dqns temp_to final 1\n");
	i = 0;
//	str = malloc(sizeof(char) * ft_lstsize(*temp_l));
	printf("dqns temp_to final 1,2\n");
	str = list_to_string(temp_lbis);
//	while (temp_lbis != NULL)
//	{
//	printf("dqns temp_to final 2\n");
/*		str[i] = *((char*)temp_lbis->content);
		i++;
		parcour_l = temp_lbis;
		temp_lbis = temp_lbis->next;

	printf("dqns temp_to final 3\n");
		free(parcour_l);*/
//	}
//	printf("dans temp final %s\n",str);
	
	*temp_l = NULL;
	ft_lstadd_back(final_l, ft_lstnew(new_block(str, f)));
}

void	handle_separator(t_var_toblock *var, char *line, t_list **final_l, t_list **temp_l)
{
	printf("dans handle sep |%c|\n",line[var->i]);
	if (*temp_l != NULL)
	{
		temp_to_final(final_l, temp_l, var->f);
	}	
		if(line[var->i] == ' ')
	{
	printf("dans handle space\n");
		ft_lstadd_back(final_l, ft_lstnew(new_block(" ", space)));
		while (line[var->i] == ' ')
			var->i = var->i + 1;
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

	printf("dans dans == '0' \n");
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
void	dollar(t_var_toblock *var, char *line, t_list **temp_l)
{
	printf("start $\n");
	t_list *env_var;
	char *str;
	char *env;
	var->i = var->i + 1;
	env_var = NULL;
	if (line[var->i] == '\'' || line[var->i] == '\"')
	{
		return ;
	}
	if (line[var->i] == '\\')
	{
		ft_lstadd_back(temp_l, ft_lstnew("$"));	
		if (line[var->i + 1] == '\0')
		{
			//todo
			return;
		}
		else
		{
			var->i = var->i + 1;
		}
	}
	else
	{
		printf(" else$\n");
		while (!(is_separator_for_dollar(&line[var->i])))
		{	
			ft_lstadd_back(&env_var, ft_lstnew(&line[var->i]));
			var->i = var->i + 1;
		}
		str = list_to_string(env_var);
		printf("DANS $ str = %s\n",str);
		if ((env = getenv(str)) != NULL)
		{
			printf("DANS $ env = %s len = %zu\n",env,ft_strlen(str));
			str_to_list(env, temp_l);
		}
		else
		{
			return;
		}
	}	
}

void 	to_block(char *line, t_list **final_l)
{
	printf("mais wtf |%s|\n",line);
	t_var_toblock var;
	t_list	*temp_l;
	temp_l = NULL;
	var.i = 0;
	var.spe = 0;
	var.end_while = 1;
	while (var.end_while)
	{
		printf("i = %i c = %c  end = %i\n",var.i,line[var.i], var.end_while);
	 if (is_separator(&line[var.i]))
			handle_separator(&var, line, final_l, &temp_l);
	else if (line[var.i] == '\'')
		in_quote(line, &var, &temp_l);
	 else if(line[var.i] == '$')
	 	dollar(&var, line, &temp_l);
	//else if (line[var.i] == '\"')
	//	in_double_quote(line, &var.i, temp_l);
	//else if (line[var.i] == '\\')
	//	spe in_back_slash(line, &var.i, temp_l);
	else
	{
		
		printf("ici nothing\n");
		ft_lstadd_back(&temp_l, ft_lstnew(&line[var.i]));
		printf("la \n");
		var.i++;
	}		
	}
}
