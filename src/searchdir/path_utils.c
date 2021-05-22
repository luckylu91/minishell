/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:31:30 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 15:43:43 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "searchdir.h"

void	separate_last_slash(char *str, char **str_path, char **str_end)
{
	int	i_sep;

	*str_path = ft_strdup(str);
	*str_end = ft_strrchr(*str_path, '/');
	if (!*str_end)
	{
		*str_end = *str_path;
		*str_path = NULL;
	}
	else
	{
		*str_end = ft_strdup((*str_end) + 1);
		i_sep = ft_strlen(*str_path) - ft_strlen(*str_end);
		(*str_path)[i_sep] = '\0';
	}
}
