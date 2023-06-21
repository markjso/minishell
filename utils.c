/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:44:00 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/17 12:35:29 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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

int	ft_is_not_white_space(int c)
{
	if (c >= 33 && c <= 126)
		return (1);
	else
		return (0);
}

int	ft_is_quote(int c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}