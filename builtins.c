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

/* uses getcwd to get the current working
directory and store it in pwd. It uses 
printf to print the path to the console*/

void	printpwd(void)
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	g_exit_status = 0;
}

/*
Write to screen the text following the command `echo`. 
Checks for the -n flag and if it finds it sets the
flag to false so that "\n" will not be printed.*/

void	echo_cmd(char **token)
{
	int		i;
	bool	flag;

	i = 1;
	flag = true;
	while (token[i] && !ft_strcmp(token[i], "-n"))
	{
		flag = false;
		i++;
	}
	while (token[i])
	{
		printf("%s ", token[i]);
		if (token[i])
			i++;
	}
	if (flag && (i > 1))
		printf("\n");
	g_exit_status = 0;
}

char *local_split_value(char *str)
{
	char	*ret_str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i] != ':')
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

/* If no arguments entered print the env list
If arguments are entered split them using = as
a delimiter and save them in name and value
pointer. Search the t_envar linked list to see
if they already exist and if they don't initalise
a new structure and add it to the linked list.
If it does exist free the old one and update it*/

int	export_cmd(char **token, t_program *program)
{
	char	**split_env;
	char	*name;
	char	*value;
	char	*temp;
	t_envar	*node;

	if (token[1] == NULL)
	{
		print_env(program);
		return (0);
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
	if (ft_strcmp(name, "PATH") == 0)
	{
		value = local_split_value(value);
		temp = ft_strjoin((find_env(program->envar, "PATH")->value), value);
		node->value = temp;
		free(value);
	}
	else
	{
		free(node->value);
		node->value = value;
	}
	return (0);
}

/* find the env variable at argument [1] (token[1])
and remove it from the linked list of 
environment variables*/

void	unset_cmd(char **token, t_program *program)
{
	if (ft_strrchr(token[1], '#'))
	{
		error_message_cmd("invalid parameter name", 1, program);
	}
	else
		remove_env_var(token[1], program);
}

/* handles the exit command. Frees the program
structure and exits the shell*/

void	exit_cmd(char **token, t_program *program)
{
	if (token[1] && (token[2]))
		error_message_cmd("too many arguments", 255, program);
	else if (token[1])
	{
		ft_free(program);
		ft_exit(0);
	}
	else
	{
		// ft_free(program);
		ft_exit(0);
	}
}
