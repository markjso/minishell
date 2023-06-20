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

int	find_token_number(char *str, t_char_list *root)
{
	int			i;
	int			type;
	int			count;
	int			open_quote;

	i = 0;
	count = 0;
	if (ft_isprint(str[i]))
		count++;
	while (str[i] != '\0')
	{
		type = 39; // Single quote by default. 
		if ((str[i] == 34 || str[i] == 39) && str[i + 1] != '\0') //IF index i is double or single quote and next exists. 
		{
			if (str[i] == 34) // Type is double quote, else default to single quote
				type = 34;
			open_quote = i;
			i++;
			while (str[i] != '\0' && str[i] != type) // WHILE index i exists and is not (matching/closing) double quote. 
				i++;
			if (str[i] == type) // Found the matching close quote. 
			{
				char_list_insert_end(&root, open_quote, type);
				char_list_insert_end(&root, i, type); // Matching close quote.
				count++;
			}
		}
		else if ((str[i] == ' ' || str[i] == '\t') && str[i + 1] != '\0') // ELSE IF is space or tab AND next is not end of string but an actual char. Then it will be a new word. 
			count++;
			char_list_insert_end(&root, i, ' '); // add space to linked list. 
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		i++;
	}
	return (count);
}

char	*make_token(char *str, int length)
{
	int		i;
	char	*return_token;

	i = 0;
	return_token = malloc(sizeof(char) * (length));
	while (i < length - 1)
	{
		return_token[i] = str[i + 1];
		i++;
	}
	return_token[i] = '\0';
	return(return_token);
}

void	make_tokens(char *str, char **split, t_char_list **root)
{
	debugFunctionName("MAKE_TOKEN");
	int 	i;
	int 	start;
	int		j;
	i = 0;
	j = 0;
	start = 0;
	printf("HIHIHIHIHIHIHIHIHI");
	t_char_list *curr;
	curr = *root;
	
	while (curr->next->next != NULL) // While "current (open quote) -> next (close quote) -> next (open quote)" exists
	{
		printf("while");
		split[j] = make_token(&str[curr->index], curr->next->index - curr->index ); //Send data inbetween the quotes. 
		j++;
		curr = curr->next->next;
	}
}

void	parse_input(char *str, char **token)
{
	int		i;
	char	**split;
	int		token_number;
	t_char_list *root = NULL;

	debugFunctionName("PARSE_INPUT");
	token_number = find_token_number(str, root);
	printf("token number is: %d\n", token_number);
	split = malloc(sizeof(char*) * token_number + 1);
	make_tokens(str, split, &root);
	// split = ft_split(str, ' '); // Returns MALLOC string
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
	char_list_delete(&root);
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
	return (1);
}

