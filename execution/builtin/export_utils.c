/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:33:47 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 16:39:22 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_assign_operator(char *s)
{
	if (!s || !*s)
		return (ASSIGN_NONE);
	if (*s == '=')
		return (ASSIGN_EQUAL);
	if (*s == '+' && *(s + 1) == '=')
		return (ASSIGN_PEQUAL);
	return (ASSIGN_NONE);
}

int	assign_operator_offset(char *arg)
{
	int	i;

	if (!*arg)
		return (0);
	if (!ft_isalpha(*arg) && *arg != '_')
		return (0);
	i = 0;
	while (arg[i] && !is_assign_operator(arg + i))
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (0);
		i++;
	}
	return (i);
}

int	not_valid_identifier_error(char *arg)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier'\n", STDERR_FILENO);
	return (-1);
}

char	*strdup_remove_plus(char *src, int op_index)
{
	size_t	size;
	char	*dest;

	if (src[op_index] == '=')
		return (ft_strdup(src));
	size = ft_strlen(src);
	dest = ft_calloc(size, sizeof(char));
	ft_memcpy(dest, src, op_index);
	ft_strcat(dest + op_index, src + op_index + 1);
	return (dest);
}
