/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:10:49 by jchurch           #+#    #+#             */
/*   Updated: 2023/06/20 18:27:24 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_program	g_program;

// int	return_char_type(char c, char next)
// {
// 	if (c == '$' && ft_is_not_white_space(next) == 1)
// 		return (1);
// 	else if ((c == '~' || c == '|') && ft_is_not_white_space(next) == 1)
// 		return (1);
// 	else if ((c == '>' && next == '>') || (c == '<' && next == '<'))
// 		return (2);
// 	else if ((c = '>' && next == '=') || (c == '<' && next == '='))
// 		return (2);
// 	else if ((c = '>' && next == '<') || (c == '<' && next == '>'))
// 		return (2);
// 	else
// 		return (0);
// }

int	find_token_number(char *str)
{
	int			i;
	char		type;
	int			count;

	i = 0;
	count = 0;
	if (ft_isprint(str[i]))
		count++;
	type = 39; // Single quote by default. 
	while (str[i] != '\0')
	{
		if (ft_is_quote(str[i]) && str[i + 1] != '\0') //IF index i is double or single quote and next exists. 
		{
			if (str[i] == 34) // Type is double quote, else default to single quote
				type = 34;
			i++;
			while (str[i] != type && str[i] != '\0') // WHILE index i exists and is not (matching/closing) double quote. 
				i++;
			if (str[i] == type) // Found the matching close quote. 
				count++;
		}
		else if (ft_is_not_white_space(str[i] == 0) && str[i + 1] != '\0') // ELSE IF is space or tab AND next is not end of string but an actual char. Then it will be a new word. 
		{
			count++;
			while (ft_is_not_white_space(str[i] == 0))
				i++;
		}
		i++;
	}
	return (count);
}

int	find_end(char *str)
{
	int			i;
	char		type;

	i = 0;
	type = 39; // Single quote by default. 

	while (str[i] != '\0')
	{
		if (ft_is_not_white_space(str[i]) == 0) // IF whitespace, stop. 
		{
			break ;
		}
		// IF quote, ignore white space
		if (ft_is_quote(str[i]) == 1) //IF index i is double or single quote and next exists. 
		{
			if (str[i] == 34) // Type is double quote, else default to single quote
				type = 34;
			i++;
			while (str[i] != type && str[i] != '\0') // WHILE index i exists and is not (matching/closing) double quote. 
				i++;
		}
		i++;
	}
	return (i);
}

char	*make_token(char *str)
{
	debugFunctionName("MAKE_TOKEN");
	int		i;
	char	*return_token;

	i = 0;
	int length = find_end(str);
	return_token = malloc(sizeof(char) * length + 1); //JC MALLOC
	while (i < length)
	{
		return_token[i] = str[i];
		i++;
	}
	return_token[i] = '\0';
	return(return_token);
}



void	make_tokens(char *str, char **split)
{
	debugFunctionName("MAKE_TOKENS");
	int split_index;
	int input_index;

	split_index = 0;
	input_index = 0;
	while (str[input_index] != '\0')
	{
		if (ft_is_not_white_space(str[input_index]) == 1)
		{
			split[split_index] = make_token(&str[input_index]);
			input_index = ft_strlen(split[split_index]) - 1 + input_index;
			split_index++;
		}
		input_index++; // if whitespace
	}
	split[split_index] = 0;
}

void	parse_input(char *str, t_program *program)
{
	// int		i;
	// char	**split;
	int		token_number;

	debugFunctionName("PARSE_INPUT");
	token_number = find_token_number(str);
	// printf("token number is: %d\n", token_number);
	// split = malloc(sizeof(char*) * token_number + 1);
	program->token = malloc(sizeof(char*) * token_number + 1);
	make_tokens(str, program->token);
	// split = ft_split(str, ' '); // Returns MALLOC string
	// if (!split) // When does this get called?
	// 	printf("empty string\n");
	// return (split);
	// i = 0;
	// while (split[i]) //Each i is a string in it self as split is whole words without spaces. 
	// {
	// 	token[i] = split[i];
	// 	printf("token[%d]: %s\n", i, token[i]);
	// 	i++;
	// }
	// token[i] = 0;
	// int j = 0;
	// while (j < i)
	// 	free(split[j++]);
	// free(split);
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
void	process_input(char *str, t_program *program)
{
	debugFunctionName("PROCESS_INPUT");
	parse_input(str, program);
}
