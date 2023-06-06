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

