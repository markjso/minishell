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

/* Write to screen the text following the command `echo`. 
Checks for the -n flag and if it finds it sets the
flag to false so that "\n" will not be printed.*/

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
	// free(value);
}

/* If no arguments entered print the env list
If arguments are entered split them using = as
a delimiter and save them in name and value
pointer. Search the t_envar linked list to see
if they already exist and if they don't initalise
a new structure and add it to the linked list.
If it does exist free the old one and update it*/

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
	free(split_env);
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
	// free(split_env);
}

/* find the env variable at argument [1] (token[1])
and remove it from the linked list of 
environment variables*/

void	unset_cmd(char **token, t_program *program)
{
	if (token[1] == NULL)
		return ;
	if (ft_strrchr(token[1], '#'))
		error_message_cmd("invalid parameter name", 1, program);
	else
		remove_env_var(token[1], program);
}
