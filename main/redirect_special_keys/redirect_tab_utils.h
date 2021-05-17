/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tab_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:15:19 by lzins             #+#    #+#             */
/*   Updated: 2021/05/17 16:28:37 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_TAB_UTILS_H
# define REDIRECT_TAB_UTILS_H

#include "minishell.h"

int		startswith(char *str, char *prefix);
char	last_char(char *str);
t_block	*valid_last_block(void);
void	show_matching_files(t_list *files, t_minishell *ms);
void	separate_last_slash(char *str, char **str_path, char **str_end);
void	get_contextual_tabinfo(t_tabinfo *tabinfo);
void	common_prefix_fun(char *str, char **prefix);

#endif