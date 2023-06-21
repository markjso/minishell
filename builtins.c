/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:55:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/20 18:25:54 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program g_program;

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
void echo_cmd(char **token)
{
    debugFunctionName("ECHO_CMD");
    int i = 1;
    int no_newline = 0;

    // Check if -n option was passed
    if (token[i] && ft_strcmp(token[i], "-n") == 0)
    {
        no_newline++;
        i++;
    }

    // Print the arguments
    while (token[i])
    {
        printf("%s ", token[i]);
        i++;
    }

    // Print a new line only if -n option was not passed and there are arguments
    if (!no_newline && (i > 1))
    {
        printf("\n");
    }
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
        return 0;
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
	return (0);
}

/*
Always returns 0?
*/