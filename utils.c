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

char	*find_append_value(char *str)
{
	char	*ret_str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i] != ':' && str[i])
		i++;
	k = i;
	while (str[i] != '\0')
	{
		j++;
		i++;
	}
	i = 0;
	ret_str = malloc(sizeof(char *) * j);
	while (str[k] != '\0')
	{
		ret_str[i] = str[k];
		i++;
		k++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}

void	export_path_overwrite(t_envar *node, char *value)
{
	free(node->value);
	node->value = value;
}
