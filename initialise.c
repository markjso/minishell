/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:44:30 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/01 16:14:56 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_free(char *temp, char *input)
{
	if (input)
		free(input);
	if (temp)
		free(temp);
}

int	takeInput(char *str)
{
	char	*input;
	char	*username;
	char	*temp;

	username = getenv("USER");
	temp = ft_strjoin(username, "@>>$ "); // Return is MALLOCED
	input = readline(temp); // Return is MALLOCED
	if (!input) // Input is username and '$'.  IF username doesn't exist, exit program in error. 
	{
		printf("\n%s exit\n", temp);
		free(temp);
		exit(1);
	}
	if (ft_strlen(input) != 0) // If user inputs text, even nonsense, this is called. 
	{
		add_history(input);
		ft_strlcpy(str, input, ft_strlen(input) + 1);
		init_free(temp, input);
		return (0);
	}
	else // Else the user inputed nothing. 
	{
		init_free(temp, input);
		return (1);
	}
}
