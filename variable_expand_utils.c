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

char	*expand_dollar(char *variable, t_program *program)
{
	t_envar	*env_node;

	variable++;
	env_node = find_env(program->envar, variable);
	if (variable[0] == '?')
	{
		return (ft_itoa(g_exit_status));
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

void	skip_single_quote(char *src, int *end)
{
	(*end)++;
	while (src[*end] != 39)
	{
		(*end)++;
	}
	(*end)++;
}
