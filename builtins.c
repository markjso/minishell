/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:55:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/01 16:11:16 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printpwd(void)
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	printf("\nDir: %s", pwd);
}

int	builtins(char **token)
{
	int		no_of_builtins;
	int		i;
	char	*builtin_ID[no_of_builtins];

	no_of_builtins = 7;
	i = 0;
	builtin_ID[0] = "echo";
	builtin_ID[1] = "cd";
	builtin_ID[2] = "pwd";
	builtin_ID[3] = "export";
	builtin_ID[4] = "unset";
	builtin_ID[5] = "env";
	builtin_ID[6] = "exit";
	while (i < no_of_builtins && ft_strncmp(token[0], builtin_ID[i], 6) != 0)
	{
		i++;
	}
	if (i == 2)
		printpwd();
	else if (i == 6)
		exit(0);
	return (0);
}

void	parse_input(char *str, char **token)
{
	int		i;
	char	**split;

	split = ft_split(str, ' ');
	if (!split)
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
