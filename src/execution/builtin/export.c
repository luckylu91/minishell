/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:02:22 by lzins             #+#    #+#             */
/*   Updated: 2021/05/24 16:53:21 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	enlarge_environ(int new_size, char ***our_env)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(new_size, sizeof(char **));
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

	assign_op_code = is_assign_operator(arg + arg_offset);
	if (assign_op_code == ASSIGN_EQUAL)
		new_value = ft_strdup(arg);
	else
		new_value = ft_strjoin((*existing), arg + arg_offset + 2);
	wrap_free(*existing);
	*existing = new_value;
}

int	export_one(char *arg, char ***our_env)
{
	int	i;
	int	arg_offset;

	arg_offset = assign_operator_offset(arg);
	if (!arg_offset)
	{
		not_valid_identifier_error(arg);
		return 1;
	}
	if (!arg[arg_offset])
		return 0;
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
	return 0;
}

void	no_arg(char **our_env)
{
	int	i;

	i = 0;
	while (our_env[i] != NULL)
	{
		printf("declare -x %s\n", our_env[i]);
		i++;
	}
}

int	export(char **argv, char ***our_env)
{
	int	i;
	int	r;

	r = 0;
	i = 0;
	if (argv[1] == NULL)
		no_arg(*our_env);
	while (argv[++i])
	{
		if (r == 0)
			r = export_one(argv[i], our_env);
		else 
			export_one(argv[i], our_env);
	}
	return (r);
}
