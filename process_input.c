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

int	find_token_number(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (ft_isprint(str[i]))
		count++;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && str[i + 1] != '\0') //IF index i is double quote and next exists. 
		{
			i++;
			while (str[i] != '\0' && str[i] != 34) // WHILE index i exists and is not (matching/closing) double quote. 
				i++;
		}
		else if (str[i] == 39 && str[i + 1] != '\0') //IF index i is single quote and next exists. 
		{
			i++;
			while (str[i] != '\0' && str[i] != 39) // WHILE index i exists and is not (matching/closing) single quote. 
				i++;
		}
		else if (str[i + 1] != '\0' && (str[i] == 32 || str[i] == 9)) // ELSE IF is space or tab AND next is not end of string but an actual char. Then it will be a new word. 
			count++;
			// while (str[i] == 'sp' || str[i] == 'ht')
			// 	i++;
		i++;
	}
	return (count);
}

char	*make_token(char *str)
{
	
}

void	make_tokens(char *str, char **split)
{
	int 	i;
	int 	start;
	char 	q;
	char	*token;
	int		j;

	i = 0;
	j = 0;
	start = 0;
	while(str[i] != '\0')
	{
		if (ft_is_not_white_space(str[i]))
		{
			split[j] = make_token(&str[i]);
			j++;
			while (!ft_is_not_white_space(str[i]))
				i++;
		}
		i++; 
	}
}

void	parse_input(char *str, char **token)
{
	int		i;
	char	**split;
	int		token_number;

	debugFunctionName("PARSE_INPUT");
	token_number = find_token_number(str);
	printf("token number is: %d\n", token_number);
	split = malloc(sizeof(char*) * token_number + 1);
	make_tokens(str, split);
	split = ft_split(str, ' '); // Returns MALLOC string
	if (!split) // When does this get called?
		printf("empty string\n");
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


    // t_envar *pwd;
    // t_envar *oldpwd;

    // pwd = find_env_var("PWD");

// void expand_input(char *str)
// {
// 	int i;
// 	int len;
// 	char *variable;
// 	t_envar	*env_var;

// 	len = 0;
// 	// WHILE the string exists, increment through each char index. 
// 	while (str[i] != '\0')
// 	{
// 		// IF current char is $ and next is alpha number, there is the potential for this to be an env var. 
// 		if (str[i] == '$' && ft_isalnum(str[i + 1] == 1))
// 		{
// 			// Get the lenth of the potential env var. 
// 			len = ft_alnum_word_len(str, i);

// 			env_var = find_env_var(*token);

// 		}
// 		// else if (str[i] == '$' && str[i + 1] == '\0'){ print dollar sign if echo $ }
// 		i++;
// 	}
// }

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

