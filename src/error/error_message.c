/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:21:17 by lzins             #+#    #+#             */
/*   Updated: 2021/04/19 11:30:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	error_message(char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (-1);
}

int	error_message_errno(char *prefix, char *errno_str)
{
	if (prefix)
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(errno_str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (-1);
}
