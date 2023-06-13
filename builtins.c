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

/*
Write to screen the text folloing the command `echo`. 
Checks for the -n flag. Must expand this description.
*/
void	echo_cmd(char **token)
{
	debugFunctionName("ECHO_CMD");
	int	i;
	int	no_newline; // flag for -n option

	i = 1;
	no_newline = 0;
	token++;
	// printf("echo_cmd token 0: %s\n", token); //this is `echo`
	// printf("echo_cmd token 1: %s\n", token); //this is the next item after `echo`
    // check if -n option was passed
	if (token[i] && ft_strcmp(token[i], "-n") == 0)
	{
		no_newline++;
		i++;
	}
	while (token[i])
	{
		if (token[i] && ft_strcmp(token[i], "-n") == 0)
		{
			printf("%s", token[i]);
			if (token[i + 1])
				printf(" ");
		}
		i++;
	}
    // print new line only if -n option was not passed and there are arguments
	if (!token[1] && no_newline)
		printf("\n");
	token--;
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
int	builtins(char **token)
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
	while (i < no_of_builtins && ft_strcmp(token[0], builtin_id[i]) != 0)
	{
		i++;
	}
	if (i == 0)
		echo_cmd(token + 1);
	else if (i == 1)
		printpwd();
	else if (i == 2)
		print_env();
	else if (i == 3)
		exit(0);
	return (0);
}
