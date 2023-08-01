/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:55:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/21 15:12:38 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_program g_program;

void	printpwd(void)
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	printf("Dir: %s\n", pwd);
    g_program.exit_status = 0;
}

/*
Write to screen the text folloing the command `echo`. 
Checks for the -n flag. Must expand this description.
*/

static	bool	check_n_flag(char *str)
{
	if (!*str)
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

void echo_cmd(char **token)
{
    debugFunctionName("ECHO_CMD");
    int i = 1;
    bool    flag;
    flag = false;

    // Check if -n option was passed
    while (token[i] && check_n_flag(token[i]))
    {
        flag = true;
        i++;
    }
    // Print the arguments
    while (token[i])
    {
        printf("%s ", token[i]);
        if (token[i])
        i++;
    }
    // Print a new line only if -n option was not passed and there are arguments
    if (!flag && (i > 1))
		printf("\n");
	g_program.exit_status = 0;
}

int	export_cmd(char **token)
{
	char	**split_env;
	char	*name;
	char	*value;
	t_envar	*node;

	if (token[1] == NULL)
    {
        // No arguments provided, print the environment variables
        print_env();
        return (0);
    }
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
	// free(name);
	// free(value);
	return (0);
}

void	exit_cmd(char **token)
{
	if (token[1] && token[2])
		(ft_putstr_fd("exit", 2), error_message("too many arguments", 255));
	else if (token[1])
	{
		ft_exit(0);
	}
	else
	{
		ft_exit(0);
	}
}