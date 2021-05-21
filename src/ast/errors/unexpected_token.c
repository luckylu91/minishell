/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:25:31 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 19:55:45 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast_api.h"

t_status	unexpected_token_error(t_list *token_lst)
{
	char	*token_str;

	token_str = to_str(token_lst);
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token_str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (STATUS_ERROR);
}
