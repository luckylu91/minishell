/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_block_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:24:39 by hgallien          #+#    #+#             */
/*   Updated: 2021/05/09 12:49:45 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "to_block.h"

void 	to_block(char *line, t_list **final_l)
{
	//printf("####\n|%s|\n####\n",line);

	t_var_toblock var;
	t_list	*temp_l;
	temp_l = NULL;
	*final_l= NULL;
	var.i = 0;
	var.spe = 0;
	var.end_while = 1;
	if (line == NULL || ft_all_in(line," "))
	  {
	  //printf("c4est comme moi\n");
	  return;
	  }
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
			else
			ft_lstadd_back(&temp_l, ft_lstnew(&line[var.i]));
			//	printf("la \n");
			var.i++;
		}		
	}	}
