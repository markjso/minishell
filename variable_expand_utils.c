/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expand_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:57:03 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/13 13:57:04 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(char *variable)
{
	t_envar	*env_node;

	variable++;
	env_node = find_env_var(variable);
	if (variable[0] == '?')
	{
		return (ft_itoa(g_program.exit_status));
	}
	if (env_node == NULL)
	{
		return ("");
	}
	else
	{
		return (env_node->value);
	}
}

int	env_len(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '?')
		return (1);
	while (ft_is_valid_var_char(str[i]) == 1)
		i++;
	return (i);
}

char	*return_string(char *src, int terminator)
{
	char		*ret;
	static char	*backup;

	if (!src)
	{
		src = backup;
	}
	ret = ft_strdup(src);
	ret[terminator] = '\0';
	return (ret);
}

void	skip_single_quote(char *src, int *end)
{
	(*end)++;
	while (src[*end] != 39)
	{
		(*end)++;
	}
	(*end)++;
}
