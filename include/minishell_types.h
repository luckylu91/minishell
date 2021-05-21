/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:49:36 by lzins             #+#    #+#             */
/*   Updated: 2021/05/20 12:06:51 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

# include "hist.h"

typedef struct	s_linebuffer
{
	char	*buffer;
	int		i_max;
	int		i;
	int		size;
}				t_linebuffer;

typedef struct		s_minishell
{
	t_hist			*h;
	int				exit_code;
	char			**env;
	t_linebuffer	*lb;
	char			**termcaps;
	char			*tabintent;
	t_list			*all_child;
	int				prompted_signal;
}	t_minishell;

typedef struct	s_tabinfo
{
	char	*basedir;
	char	*str_to_complete;
	int		do_nothing;
}	t_tabinfo;

#endif