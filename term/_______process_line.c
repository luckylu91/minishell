/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:22:26 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 11:44:08 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	process_line(char *line)
{
	if (!line)
		return ;
	if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		exit(0);
	}
	free(line);
}
