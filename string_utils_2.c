/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:33:55 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/18 15:36:47 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int	ft_white_space(int c)
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

void	init_envp_first_run(t_program *program, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[j])
		j++;
	program->envp = (char **)malloc(sizeof(char *) * (j + 1));
	while (i < j)
	{
		program->envp[i] = ft_strdup(envp[i]);
		i++;
	}
}
