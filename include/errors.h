/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:39:54 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 20:40:47 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "ast_api.h"
# include <string.h>
# include <errno.h>

int			bash_error_errno(char *path);
int			bash_error_errno_arg(char *path, char *arg);
t_status	unexpected_token_error(t_list *token_lst);

#endif