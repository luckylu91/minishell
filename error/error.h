/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:21:39 by lzins             #+#    #+#             */
/*   Updated: 2021/04/20 16:53:26 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

#include "libft.h"
#include "ast_api.h"
#include <unistd.h>

int	error_message(char *message);
int	error_message_errno(char *prefix, char *errno_str);
int	ambiguous_redirect_error(t_ast *redir_ast);

#endif
