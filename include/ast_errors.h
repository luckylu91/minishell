/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_errors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:39:54 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 19:11:56 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_ERRORS_H
# define AST_ERRORS_H

# include "ast_api.h"

t_status	unexpected_token_error(t_list *token_lst);

#endif