/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_if_needed.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:22:11 by lzins             #+#    #+#             */
/*   Updated: 2021/03/26 10:06:35 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

int	create_ast_if_needed(t_ast_type type, t_ast **result_ast)
{
	if (!*result_ast && !create_ast(type, result_ast))
		return (0);
	return (1);
}
