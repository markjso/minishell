/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:44:00 by jmarks            #+#    #+#             */
/*   Updated: 2023/06/25 21:34:46 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_special_char(char *s1)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

/*
Returns the lengh of a word - alpha numeric characters only. 
ft_alpha_word_len(char *string to use, int starting index of first char of word.)
*/
int	ft_alnum_word_len(char *str, int start)
{
	int i;

	i = start;
	while(ft_isalnum(str[i]) == 1)
		i++;
	return (i - start);
}

/*
Checks if the char is an upper case char acording to the ASCII table. 
Returns 1 if it is uppercase. 
Returns 0 if it any thing other than uppercase, including lowercase, letters, symbols, etc. 
*/
int ft_is_upper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

/*
Verify if the char is valid for a shell environment variable. 
Returns 1 if true and 0 if false.
*/
int	ft_is_valid_var_char(char c)
{
	if (c != '\0' && (ft_is_upper(c) == 1 || ft_isdigit(c) == 1 || c == 95))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}


/*
Returns the lengh of a word based on environment variable rules: 
(1) Uppercase, (2) Numeric, (3) Underscores.
Don't sent the dollar sign ($) as it will not process. 
ft_env_word_len(char *string to use, int starting index of first char of word.)
*/
int	ft_env_word_len(char *str)
{
	int start;
	int j;

	j = 0;
	start = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '$' && ft_is_valid_var_char(str[j + 1]) == 1) // IF is var
		{
			start = j;
			j++;
			while (ft_is_valid_var_char(str[j]))
			{
				j++;
			}
			return (start - j);
		}
		else //ELSE is not var
		{
			j++;
		}
	}
	if (str[j] == '\0')
		return (0);
	return (0); // Default return
}

/*
Checks if the char is printable ASCII 33 (!) to 126 (~) inclusive. 
Excludes space and tab. 
Returns 1 if it is between 33 to 126 inclusive. 
Returns 0 otherwise.
*/
int	ft_is_not_white_space(int c)
{
	if (c >= 33 && c <= 126)
		return (1);
	else
		return (0);
}

/*
Checks if the char is not printable: ASCII 32 (space) and less; and 127 (del). 
Returns 1 if true: it 32 or less; or 127. 
Returns 0 otherwise. 
*/
int ft_is_white_space(int c)
{
	if (c >= 33 && c <= 126)
		return (0);
	else
		return (1);
}

/*
Checks if the char is a single or double quote: ASCII 34 ("") and 39 ('). 
Returns 1 if true it is a double or single quote. 
Returns 0 otherwise. 
*/
int	ft_is_quote(int c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}

/*
Checks if the char is a single or double quote: ASCII 34 ("") and 39 ('). 
Returns 1 if true it is not a double or single quote. 
Returns 0 if it is a double or single quote. 
*/
int	ft_is_not_quote(int c)
{
	if (c == 34 || c == 39)
		return (0);
	else
		return (1);
}


/*
Checks if char agains the ASCII table. 
Returns 1: If char is not a space or tab and is not a single or double quote. 
Returns 0 otherwise. 
*/
int	ft_not_whitespace_not_quote(int c)
{
	if (ft_is_white_space(c) == 0 && ft_is_quote(c) == 0)
		return (1);
	else
		return (0);
}