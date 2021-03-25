/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_block_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgallien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:24:39 by hgallien          #+#    #+#             */
/*   Updated: 2021/03/25 14:39:09 by hgallien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "to_block.h"
int		is_separator(char *c)
{
	if (c[0] == '|' || c[0] == ' ' || c[0] == ';'  ||c[0] == '\0')
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
void		in_quote(char *line, int *i, t_list **temp_l)
{
	*i = *i + 1;
	char buffer[10];
	while (line[*i] != '\'')
	{
		if (line[*i] == '\0')
		{
			read(STDIN_FILENO, buffer, 10);
		}
		ft_lstadd_back(temp_l, ft_lstnew(&line[*i]));
		*i = *i + 1;
	}
}

void	handle_space(t_var_toblock *var, t_list **final_l,t_list **temp_l, char *line)
{
		ft_lstadd_back(final_l, ft_lstnew(new_block(" ", space)));
		while (line[var->i] == ' ')
		{
			var->i = var->i + 1;
		}
}

void	temp_to_final(t_list **final_l, t_list *temp_l, enum flags f)
{
	char *str;
	t_list *parcour_l;
	int i;

	i = 0;
	str = malloc(sizeof(char) * ft_lstsize(temp_l));
	while (temp_l != NULL)
	{
		str[i] = *((char*)temp_l->content);
		i++;
		parcour_l = temp_l;
		temp_l = temp_l->next;
		free(parcour_l);
	}
	ft_lstadd_back(final_l, ft_lstnew(new_block(str, f)));
}

void	handle_separator(t_var_toblock *var, char *line, t_list **final_l, t_list **temp_l)
{
	printf("dans handle sep |%c|\n",line[var->i]);
	temp_to_final(final_l, *temp_l, var->f);
	if(line[var->i] == ' ')
	{

	printf("dans handle space\n");
		ft_lstadd_back(final_l, ft_lstnew(new_block(" ", space)));
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
void 	to_block(char *line, t_list **final_l)
{
	printf("mais wtf\n");
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
		in_quote(line, &var.i, &temp_l);
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
