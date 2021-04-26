/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:30:50 by lzins             #+#    #+#             */
/*   Updated: 2021/04/26 11:44:08 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	termcaps_term_not_set_error(void)
{
	ft_putstr_fd("TERM is not set\n", STDERR_FILENO);
	return (-1);
}

int	termcaps_database_not_accessible(void)
{
	ft_putstr_fd("Could not access to the termcap database\n", STDERR_FILENO);
	return (-1);
}

int	termcaps_database_no_entry(char *term_type)
{
	ft_putstr_fd("Error in finding entry for ", STDERR_FILENO);
	ft_putstr_fd(term_type, STDERR_FILENO);
	ft_putstr_fd(" in the termcaps database", STDERR_FILENO);
	return (-1);
}
