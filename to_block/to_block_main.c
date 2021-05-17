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

void	setup_var(t_list **final_l, t_list **temp_l, t_var_toblock *var)
{
	temp_l = NULL;
	*final_l = NULL;
	var->i = 0;
	var->spe = 0;
	var->end_while = 1;
}

void	if_forest(t_var_toblock *var, t_list **temp_l,
		t_list **final_l, char *line)
{
	if (is_separator(&line[var->i]))
		handle_separator(var, line, final_l, temp_l);
	else if (test_redir(line, var, *temp_l))
		redirection(var, line, final_l, temp_l);
	else if (line[var->i] == '\'')
		in_quote(line, var, temp_l);
	else if (line[var->i] == '$')
		ft_dollar(var, line, temp_l, final_l);
	else if (line[var->i] == '\"')
		in_double_quote(line, var, final_l, temp_l);
	else if (line[var->i] == '\\')
		in_back_slash(line, var, final_l, temp_l);
	else
	{
		if (line[var->i] == '~')
			in_tild(line, var, final_l, temp_l);
		else
			ft_lstadd_back (temp_l, ft_lstnew(&line[var->i]));
		var->i = var->i + 1;
	}	
}

void 	to_block(char *line, t_list **final_l)
{
	t_var_toblock	var;
	t_list			*temp_l;

	setup_var(final_l, &temp_l, &var);
	if (line == NULL || ft_all_in(line, " "))
		return ;
	while (var.end_while)
	{
		if_forest(&var, &temp_l, final_l, line);
	}
}
