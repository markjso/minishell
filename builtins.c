/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:55:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/17 13:45:55 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envar	*g_env_vars;

void	printpwd(void)
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	printf("\nDir: %s", pwd);
}

// void	echo_cmd(char **token)
/*
Write to screen the text folloing the command `echo`. 
Checks for the -n flag. Must expand this description.
*/
void	echo_cmd(t_data *data)
{
	debugFunctionName("ECHO_CMD");
	int	i;
	int	no_newline; // flag for -n option

	i = 1;
	no_newline = 0;
	data->token++;
	// printf("echo_cmd data_token 0: %s\n", *data->token); //this is `echo`
	// printf("echo_cmd data_token 1: %s\n", *data->token); //this is the next item after `echo`
    // check if -n option was passed
	if (data->token[i] && ft_strcmp(data->token[i], "-n") == 0)
	{
		no_newline++;
		i++;
	}
	while (data->token[i])
	{
		if (data->token[i] && ft_strcmp(data->token[i], "-n") == 0)
		{
			printf("%s", data->token[i]);
			if (data->token[i + 1])
				printf(" ");
		}
		i++;
	}
    // print new line only if -n option was not passed and there are arguments
	if (!data->token[1] && no_newline)
		printf("\n");
	data->token--;
}

int	export_cmd(char **token)
{
	char	**split_env;
	char	*name;
	char	*value;
	t_envar	*node;

	split_env = ft_split(token[1], '=');
	if (!split_env[1])
		return (1);
	name = ft_strdup(split_env[0]);
	value = ft_strdup(split_env[1]);
	node = find_env_var(name);
	if (node == NULL)
	{
		node = init_env(name, value);
		add_env_var(node);
	}
	else
	{
		free(node->value);
		node->value = value;
	}
	return (0);
}

/*
Always returns 0?
*/
int	builtins(t_data *data)
{
	int		no_of_builtins;
	int		i;

	debugFunctionName("BUILTINS");
	no_of_builtins = 4;
	char	*builtin_id[4];
	i = 0;
	builtin_id[0] = "echo";
	builtin_id[1] = "pwd";
	builtin_id[2] = "env";
	builtin_id[3] = "exit";
	while (i < no_of_builtins && ft_strcmp(data->token[0], builtin_id[i]) != 0)
	{
		i++;
	}
	if (i == 0)
		echo_cmd(data);
		// echo_cmd(data->token + 1);
	else if (i == 1)
		printpwd();
	else if (i == 2)
		print_env();
	else if (i == 3)
		exit(0);
	return (0);
}

void	parse_input(char *str, t_data *data)
{
	int		i;
	char	**split;

	debugFunctionName("PARSE_INPUT");
	split = ft_split(str, ' '); // Returns MALLOC string
	if (!split) // When does this get called?
	{
		printf("empty string\n");
	}
	i = 0;
	while (split[i]) //Each i is a string in it self as split is whole words without spaces. 
	{
		data->token[i] = split[i];
		// printf("data->token[%d]: %s\n", i, data->token[i]);
		i++;
	}
	data->token[i] = NULL;
	free(split);
}

/*1st arg: str is raw user input. 
2nd arg: **token is empty pointer to string that will become tokenised string; 
or in parse_quotes branch becomes pointer to struct t_data*/
int	process_input(char *str, t_data *data)
// int	process_input(char *str, char **token)
{
	debugFunctionName("PROCESS_INPUT");
	parse_input(str, data);
	// tampvar is just for debugging purposes. Can cahange back to `if (builitins(data))`. 
	int tempvar = builtins(data);
	printf("Builtins return value: %d\n", tempvar);
	if (tempvar) //If not 1 or greater
		return (0);	
	else // Else 0 or less ??Always this??
		return (1);
}
