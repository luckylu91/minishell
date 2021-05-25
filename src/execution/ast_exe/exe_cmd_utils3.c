/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:53:27 by lzins             #+#    #+#             */
/*   Updated: 2021/05/25 19:14:56 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_slash(char *c)
{
	return (*c == '/');
}

int	contains_slash(char *str)
{
	return (ft_any(str, ft_strlen(str), 1, (t_bool_fun)is_slash));
}

int	overflow_fd(t_list *l, fd_err *err)
{
	if (redir_fd_at(l->content) > 255)
		return (set_error_three(l, err));
	else
		return (0);
}
