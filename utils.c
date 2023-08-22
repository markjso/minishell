/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:44:00 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/25 21:34:46 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*local_find_env_name(char *str)
{
	char	*ret_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		i++;
	}
	ret_str = malloc(sizeof(char *) * i);
	while (j < i)
	{
		ret_str[j] = str[j];
		j++;
	}
	ret_str[j] = '\0';
	return (ret_str);
}
