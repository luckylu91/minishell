/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:53:27 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 15:55:11 by lzins            ###   ########lyon.fr   */
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
