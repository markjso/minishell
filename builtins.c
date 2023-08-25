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

int	export_name_cheker(char *token)
{
	int	i;

	if (!ft_is_upper(token[0]) && token[0] != '_')
		return (-2);
	i = 1;
	while(token[i] && token[i] != '=')
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
			&& (token[i++] = 'T') && (token[i] == 'H'))
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
	int		checker;

	if (token[1] == NULL)
	{
		print_env(program);
		return ;
	}
	checker = export_checker(token[1]);
	if (checker == -1)
		printf("Invalid export command. Only one and only one equals is required\n");
	if (checker == -2)
		printf("Invalid env name\n");
	if (checker == -3)
		printf("No value for env given\n");
	if (checker < 0)
		return ;
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
	if (ft_strcmp(name, "PATH") == 0 && append_checker(value) == 1)
		export_path_append(value, program, node);
	else
		export_path_overwrite(node, value);
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
