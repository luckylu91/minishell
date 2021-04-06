/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_toblock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgallien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:35:19 by hgallien          #+#    #+#             */
/*   Updated: 2021/04/06 15:35:29 by hgallien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "to_block.h"


void	is_finished(char *line)
{
	int dquote;
	int quote;
	int backslash;
	int i;

	dquote= 1;
	quote = 1;
	backslash = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && dquote * backslash == 1)
			quote = quote * -1;
		else if (line[i] == '\"' && quote * backslash == 1)
			quote = quote * -1;
		else if (line[i] == '\\' && quote == 1)
			backslash = backslash * -1;
		i++;
	}
}
