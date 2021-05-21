/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_semicol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:20:18 by lzins             #+#    #+#             */
/*   Updated: 2021/03/31 11:34:45 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

int	identify_semicol(t_list **tokens)
{
	if (is_semicol_lst(*tokens))
	{
		*tokens = ft_lststep(*tokens, 1);
		return (1);
	}
	return (0);
}
