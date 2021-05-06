/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini_context.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:08:44 by lzins             #+#    #+#             */
/*   Updated: 2021/05/05 09:12:05 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini_context *free_error(t_mini_context *mc)
{
	destroy_hist(&mc->h);
	free(mc);
	return (NULL);
}

t_mini_context	*init_mini_context()
{
	t_mini_context *mc;

	mc = ft_calloc(1, sizeof(t_mini_context));
	if (!mc)
		return (NULL);
	mc->h = create_hist(".hist_file");
	if (!mc->h)
		return (free_error(mc));
}
