/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:06:55 by lzins             #+#    #+#             */
/*   Updated: 2021/04/19 12:07:52 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	ft_splitclear(char **splitted, int i_start)
{
	int	i;

	i = i_start;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}