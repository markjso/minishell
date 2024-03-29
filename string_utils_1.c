/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:33:57 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/18 15:35:35 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checks if the char is an upper case char acording to the ASCII table. 
Returns 1 if it is uppercase. 
Returns 0 if it any thing other than uppercase, including lowercase, 
letters, symbols, etc. 
*/
int	ft_is_upper(char c)
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
	int	start;
	int	j;

	j = 0;
	start = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '$' && ft_is_valid_var_char(str[j + 1]) == 1)
		{
			start = j;
			j++;
			while (ft_is_valid_var_char(str[j]))
			{
				j++;
			}
			return (start - j);
		}
		else
		{
			j++;
		}
	}
	if (str[j] == '\0')
		return (0);
	return (0);
}

void	printpwd(void)
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	g_exit_status = 0;
}

void	add_env_var_norm(t_program *program, t_envar *tmp, t_envar *node)
{
	tmp = program->envar;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = node;
}
