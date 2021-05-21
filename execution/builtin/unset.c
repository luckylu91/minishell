/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:30:38 by lzins             #+#    #+#             */
/*   Updated: 2021/05/21 16:39:12 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"



int	find_var(char *arg, char **env)
{
	int	i;
	int	j;
	i = 0;
	//printf("debut find var\n");
	while (env[i] != NULL)
	{

		//printf("while i = %i find var\n",i);
		//printf("arg = %s env = %s\n",arg, env[i]);
		j = 0;
		while (arg[j] && env[i][j] && (arg[j] == env[i][j]))
		{
			j++;
			//printf("premier while j = %i i = %i\n",j,i);
		}
		//printf("after while find var\n");
		//printf(" arg = %c\n",arg[j]);

		//printf(" env = %c\n",env[i][j]);
		if (arg[j] == '\0' && env[i][j] == '=')
		{
			//printf("premier reurn find_var\n");
			return (i);
		}
		//printf(" fin find var\n");
		i++;
	}

	//printf("fim find var\n");
	return (-1);
}

char	**env_new_alloc(char **arg, char **env, int old)
{
	int		i;
	int		j;
	int		x;
	char	**new;

	(void)arg;
	j = 0;
	x = 0;
	i = 0;
	//printf("debut env_new\n");
	while (((env)[i]) != NULL)
	{

	//	printf("premmier while i = %i env_new\n",i);
		i++;
	}
	new = wrap_malloc(sizeof(char*)*i);
	while (j < i - 1)
	{

	//	printf("deuxieme while j = %i env_new\n",j);
		if (x != old)
		{
			new[j] = ft_strdup((env)[x]);
			j++;
		}
		wrap_free((env)[x]);
		x++;
	}
	//printf("after deuxieme zhile env new\n");
	wrap_free((env));
	new[j] = NULL;
	return (new);
}
int	not_valid_id(char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(arg[i])))
		return (1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && !(arg[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int	our_unset(char **arg, char ***env)
{
	int	i;
	int	j;
	i = 1;
	//printf("debut unset\n");
	while (arg[i] != NULL)
	{

	//	printf("while i = %i unset arg = %s\n",i,arg[i]);

		j = find_var(arg[i], *env);
	//	printf("apres find_var j = %i\n",j);
		if (not_valid_id(arg[i]))
		{
			ft_putstr_fd("'",2);
			ft_putstr_fd(arg[i],2);
			ft_putstr_fd("':not a valid identifier\n",2);
			//printf("'%s': not a valid identifier\n",arg[i]);
		}
		else 
		{
			if (j > 0)
				*env = env_new_alloc(arg, *env, j);
		}
		i++;
	}
return (1);
}
