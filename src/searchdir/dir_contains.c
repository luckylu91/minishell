/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_contains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:45:46 by lzins             #+#    #+#             */
/*   Updated: 2021/05/20 15:35:20 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "searchdir.h"

int	dir_contains(char *dir_name, char *fname)
{
	DIR				*dir;
	struct dirent	*file;
	int				ret;

	dir = opendir_err(dir_name);
	if (!dir)
		return (-1);
	file = readdir(dir);
	ret = 0;
	while (file)
	{
		if (ft_strcmp(file->d_name, fname) == 0)
		{
			ret = 1;
			break ;
		}
		file = readdir(dir);
	}
	if (closedir_err(dir) == -1)
		return (-1);
	return (ret);
}

int	list_dir(char *dir_name, t_list **alst)
{
	DIR				*dir;
	struct dirent	*file;

	dir = opendir_err(dir_name);
	if (!dir)
		return (-1);
	file = readdir(dir);
	*alst = NULL;
	while (file)
	{
		if (ft_strcmp(file->d_name, ".") != 0
			&& ft_strcmp(file->d_name, "..") != 0)
			ft_dupstr_back(alst, file->d_name);
		file = readdir(dir);
	}
	if (closedir_err(dir) == -1)
		return (-1);
	return (1);
}
