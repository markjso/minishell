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

void	echo_cmd(char **token)
{
	int	i;
	int	no_newline; // flag for -n option

	i = 1;
	no_newline = 0;
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

int	builtins(char **token)
{
	int		no_of_builtins;
	int		i;

	no_of_builtins = 5;
	char	*builtin_ID[no_of_builtins];
	i = 0;
	builtin_ID[0] = "echo";
	builtin_ID[1] = "cd";
	builtin_ID[2] = "pwd";
	builtin_ID[3] = "env";
	builtin_ID[4] = "exit";
	while (i < no_of_builtins && ft_strcmp(token[0], builtin_ID[i]) != 0)
	{
		i++;
	}
	if (i == 0)
		echo_cmd(token + 1);
	else if (i == 1)
		cd_command(token);
	else if (i == 2)
		printpwd();
	else if (i == 3)
		print_env();
	else if (i == 4)
		exit(0);
	return (0);
}

void	parse_input(char *str, char **token)
{
	int		i;
	char	**split;

	split = ft_split(str, ' '); // Returns MALLOC string
	if (!split) // When does this get called?
	{
		printf("empty string\n");
	}
	i = 0;
	while (split[i])
	{
		token[i] = split[i];
		i++;
	}
	token[i] = NULL;
	free(split);
}

int	process_input(char *str, char **token)
{
	parse_input(str, token);
	if (builtins(token))
		return (0);
	else
		return (1);
}
