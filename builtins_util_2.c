/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_util_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:55:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 15:06:24 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_name_cheker(char *token)
{
	int	i;

	if (!ft_is_upper(token[0]) && token[0] != '_')
		return (-2);
	i = 1;
	while (token[i] && token[i] != '=')
	{
		if (!ft_is_upper(token[i]) && token[i] != '_'
			&& !ft_isdigit(token[i]))
		{
			return (-2);
		}
		i++;
	}
	return (1);
}

int	append_checker(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '=')
		i++;
	i++;
	if (token[i + 4] != '\0')
	{
		if ((token[i++] == '$') && (token[i++] == 'P') && (token[i++] == 'A')
			&& (token[i++] == 'T') && (token[i] == 'H'))
		{
			return (1);
		}
		else
			return (-1);
	}
	else
		return (-1);
}

int	export_checker(char *token)
{
	int	i;
	int	equals;
	int	ret;

	ret = 0;
	equals = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
		{
			equals++;
			if (equals == 1 && token[i + 1] == '\0')
				return (-3);
		}
		i++;
	}
	if (equals != 1)
		return (-1);
	ret = export_name_cheker(token);
	if (ret == -2)
		return (-2);
	return (0);
}

void	export_cmd_norm(t_program *program, char *name, char *value)
{
	t_envar	*node;

	node = find_env(program->envar, name);
	if (node == NULL)
	{
		node = init_env(name, value);
		add_env_var(node, program);
	}
	if (ft_strcmp(name, "PATH") == 0 && append_checker(value) == 1)
		export_path_append(value, program, node);
	else
		export_path_overwrite(node, value);
}
