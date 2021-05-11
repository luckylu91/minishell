/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:02:22 by lzins             #+#    #+#             */
/*   Updated: 2021/05/08 15:14:38 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_assign_operator(char *s)
{
	int	is_equal;
	int	is_pequal;

	if (!s || !*s)
		return (ASSIGN_NONE);
	if (*s == '=')
		return (ASSIGN_EQUAL);
	if (*s == '+' && *(s + 1) == '=')
		return (ASSIGN_PEQUAL);
	return (ASSIGN_NONE);
}

// [_a-zA-Z][_0-9a-zA-Z]*
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

static int	not_valid_identifier_error(char *arg)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier'\n", STDERR_FILENO);
	return (-1);
}

static void	enlarge_environ(int new_size, char***our_env)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(new_size, sizeof(char *));
	i = -1;
	while ((*our_env)[++i])
		new_env[i] = (*our_env)[i];
	wrap_free(*our_env);
	*our_env = new_env;
}

static void	replace_existing(char *arg, char **existing, int arg_offset)
{
	int		assign_op_code;
	char	*new_value;
	int		existing_offset;

	assign_op_code = is_assign_operator(arg + arg_offset);
	if (assign_op_code == ASSIGN_EQUAL)
		new_value = ft_strdup(arg);
	else
		new_value = ft_strjoin((*existing), arg + arg_offset + 2);
	wrap_free(*existing);
	*existing = new_value;
}


static char	*strdup_remove_plus(char *src, int op_index)
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

static void	export_one(char *arg, char ***our_env)
{
	int		i;
	int		arg_offset;

	arg_offset = assign_operator_offset(arg);
	if (!arg_offset)
	{
		not_valid_identifier_error(arg);
		return ;
	}
	if (!arg[arg_offset])
		// export, no assignment. only thing to do would be export the existing variable e.g. '$> a=0 ; export a'
		return ;
	i = -1;
	while ((*our_env)[++i])
	{
		if (ft_strncmp(arg, (*our_env)[i], arg_offset) == 0)
			break ;
	}
	if ((*our_env)[i])
		replace_existing(arg, (*our_env) + i, arg_offset);
	else
	{
		enlarge_environ(i + 2, our_env);
		(*our_env)[i] = strdup_remove_plus(arg, arg_offset);
	}
	return ;
}

int	export(char **argv, char ***our_env)
{
	int			i;

	i = 0;
	while (argv[++i])
		export_one(argv[i], our_env);
	return (0);
}
