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

// t_program g_program;

void	printpwd(void)
{
	printf("%s\n", (char *)find_env(g_program.envar, "PWD")->value);
	g_program.exit_status = 0;
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
		print_env();
		return (0);
	}
	split_env = ft_split(token[1], '=');
	if (!split_env[1])
		return (1);
	name = split_env[0];
	value = split_env[1];
	node = find_env(g_program.envar, name);
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

void	unset_cmd(char **token)
{
	if (ft_strrchr(token[1], '#'))
	{
		error_message_cmd("invalid parameter name", 1);
	}
	else
		remove_env_var(g_program.token[1]);
}

void	exit_cmd(char **token)
{
	if ((token[0]) && (!token[2])) 
		error_message_cmd("too many arguments", 255);
	// else if (token[1])
	// {
	// 	ft_exit(0);
	// }
	else
	{
		ft_exit(0);
	}
}
