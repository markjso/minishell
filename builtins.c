/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:55:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/08/02 15:06:24 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_n_flag(char *str)
{
	if (!str)
		return (false);
	if (*str == '-' && *(str + 1))
	{
		str++;
		while (*str == 'n')
			str++;
	}
	if (*str)
		return (false);
	return (true);
}

/*
Write to screen the text folloing the command `echo`. 
Checks for the -n flag. Must expand this description.
*/
void	echo_cmd(char **token)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	while (token[i] && ft_check_n_flag(token[i]) == true)
	{
		flag = true;
		i++;
	}
	while (token[i])
	{
		printf("%s", token[i]);
		if (!flag)
			printf(" ");
		if (token[i])
			i++;
	}
	if (!flag && (i > 1))
		printf("\n");
	g_exit_status = 0;
}

void	export_path_append(char *value, t_program *program, t_envar *node)
{
	char	*temp;

	value = find_append_value(value);
	temp = ft_strjoin((find_env(program->envar, "PATH")->value), value);
	free(node->value);
	node->value = ft_strdup(temp);
	free(value);
}

void	export_cmd(char **token, t_program *program)
{
	char	**split_env;
	char	*name;
	char	*value;
	t_envar	*node;

	if (token[1] == NULL)
	{
		print_env(program);
		return ;
	}
	split_env = ft_split(token[1], '=');
	name = split_env[0];
	value = split_env[1];
	node = find_env(program->envar, name);
	if (node == NULL)
	{
		node = init_env(name, value);
		add_env_var(node, program);
	}
	if (ft_strcmp(name, "PATH") == 0 && check_for_colon(value) == 1)
		export_path_append(value, program, node);
	else
		export_path_overwrite(node, value);
}

void	unset_cmd(char **token, t_program *program)
{
	if (ft_strrchr(token[1], '#'))
		error_message_cmd("invalid parameter name", 1, program);
	else
		remove_env_var(token[1], program);
}
