/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:43:54 by lzins             #+#    #+#             */
/*   Updated: 2021/05/22 15:43:54 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "searchdir.h"

static int	is_slash(char c)
{
	return (c == '/');
}

static int	compute_new_size(char *path, char **cwd)
{
	int	size;
	int	i;
	int	just_met_slash;

	size = 0;
	i = 0;
	*cwd = NULL;
	just_met_slash = 1;
	if (ft_strncmp("./", path, 2) == 0)
	{
		*cwd = our_getcwd();
		size += ft_strlen(*cwd) + 1;
	}
	while (path[i])
	{
		if (ft_strncmp("./", path + i, 2) == 0 && just_met_slash)
		{
			just_met_slash = 1;
			i += 2;
			continue ;
		}
		just_met_slash = is_slash(path[i]);
		i++;
		size++;
	}
	return (size);
}

void	replace_dot_dir(char **path_addr)
{
	int		just_met_slash;
	char	*new_path;
	char	*new_path_begin;
	char	*cwd;
	char	*path;

	path = *path_addr;
	new_path = ft_calloc(compute_new_size(path, &cwd) + 1, sizeof(char));
	new_path_begin = new_path;
	if (cwd)
	{
		new_path = ft_strcat_and_move(new_path, cwd);
		*(new_path++) = '/';
	}
	while (*path)
	{
		if (ft_strncmp("./", path, 2) == 0 && just_met_slash)
		{
			just_met_slash = 1;
			path += 2;
			continue ;
		}
		just_met_slash = is_slash(*path);
		*new_path = *path;
		path++;
		new_path++;
	}
	wrap_free(*path_addr);
	*path_addr = new_path_begin;
}
