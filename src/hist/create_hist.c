/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:09:30 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 17:54:55 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

static int	get_env_number(char *env_name)
{
	char	*str;

	str = getenv(env_name);
	if (str)
	{
		if (ft_atoi_overflows(str))
			return (-1);
		return (ft_atoi(str));
	}
	return (-1);
}

t_hist	*create_hist(char *histfile_path)
{
	t_hist	*h;

	h = ft_calloc(1, sizeof(t_hist));
	h->hist_size = get_env_number("HISTSIZE");
	h->histfile_size = get_env_number("HISTFILESIZE");
	if (histfile_path)
		h->histfile_path = ft_strdup(histfile_path);
	h->position_state = BOTTOM;
	if (histfile_path && read_truncate_histfile(h) == -1)
	{
		destroy_hist(&h);
		return (NULL);
	}
	h->len = ft_bilstsize(h->hlines);
	return (h);
}
