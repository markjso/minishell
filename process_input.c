/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pprocess_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:10:49 by jchurch           #+#    #+#             */
/*   Updated: 2023/06/06 11:11:09 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envar	*g_env_vars;

void	parse_input(char *str, char **token)
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
		token[i] = split[i];
		// printf("token[%d]: %s\n", i, token[i]);
		i++;
	}
	token[i] = NULL;
	free(split);
}

/*
process_input(char *str: raw user input, char **token: is empty pointer to string that will become tokenised string).
Return value is always 0? Why
*/
int	process_input(char *str, char **token)
{
	debugFunctionName("PROCESS_INPUT");
	parse_input(str, token);
	// tampvar is just for debugging purposes. Can cahange back to `if (builitins(token))`. 
	// if (builtins(token));
	int tempvar = builtins(token);
	printf("Builtins return value: %d\n", tempvar);
	if (tempvar)
		return (0);	
	else
		return (1);
}

