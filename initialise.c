/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:44:30 by jmarks            #+#    #+#             */
/*   Updated: 2023/04/12 15:46:35 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int takeInput(char *str)
{
	char *input;
	char *username;
	char *temp;
	
	username = getenv("USER");
	temp = ft_strjoin(username, "@>>$ ");
	input = readline(temp);
	if (!input) 
		{
            printf("\n%s exit\n", temp);
            exit(1);
        }
		if (ft_strlen(input) != 0)
		{
			add_history(input);
			strcpy(str, input);
			return (0);
		}
		else
		{
			return (1);
		}
	free(input);
	free(temp);
}


