/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:07:23 by lzins             #+#    #+#             */
/*   Updated: 2021/04/27 19:02:45 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIST_H
#define HIST_H

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

typedef struct	s_hist
{
	int		hist_size;
	int		histfile_size;
	char	*histfile_name;
	t_list	*lines;
	int		index; // <- ou on en est actuellement ds la navigation
	int		size; // taille actuelle de lines (gerder <= histsize)
}	t_hist;

#endif
