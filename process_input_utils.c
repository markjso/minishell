/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <jmarks@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:11:00 by jchurch           #+#    #+#             */
/*   Updated: 2023/07/13 14:11:00 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern	t_program	g_program;

/*Input: string to return an integer the number of "tokens" that can be 
created. A token is seperated by a space or tab, unless the space or tab 
is enclosed within matching double or single quotation marks. 

Any word that has no space or no tab and is next to the "outside" of a 
quotation mark: One token will be created to encompas the outside word 
and the whole quotation mark.*/
int	find_token_number(t_token_list **root)
{
	int			i;
	t_token_list *curr;

	i = 0;
	curr = *root;
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}


int	ft_is_pipe_or_redirect(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

/*Returns the index number of a string, the return value is the first space or 
tab to occur. Spaces within matching double or single quotation marks are 
ignored. The quotation is treated as one word. 

Any word that has no space or no tab and is next to the "outside" of a 
quotation mark: One token will be created to encompas the outside word 
and the whole quotation mark...

...Unless pipe and redirectino operators are found outisde of quotes. Then 
the redirection operator or pipe will be its own token regardless if 
it buts-up against another word or quote. */
int	find_end(char *str)
{
	int			i;
	char		type;

	i = 0;
	while (str[i] != '\0')
	{	
		if (i == 0 && ft_is_pipe_or_redirect(str[i]) == 1) // if at start of new string and is special
		{
			i++;			// Increment over special
			//>bb
			// i			<- return this to make token: '>'
			if (str[i] == str[i - 1]) // If this one is same type as previous we just incremented over
			{
				i++;		// Increment 2nd over special
				//>>bb
				//  i			<- return this to make token: '>>'
			}
			break ;
		}
		if (ft_is_pipe_or_redirect(str[i]) == 1) // Not index 0, Current is special, next is not
		{
			//aa>>bb
			//  i		<- return that to make token: aa
			break ;
		}
		if (ft_is_white_space(str[i]) == 1) // IF whitespace, stop. 
			break ;
		if (ft_is_quote(str[i]) == 1) // IF quote, ignore white space
		{
			type = str[i]; // Set type to quote type. 
			i++;
			while (str[i] != type && str[i] != '\0') // WHILE index i exists and is not (matching/closing) double quote. 
				i++;
		}
		i++;
	}
	return (i);
}

/*
012346789
aaaa>>bbbb \0

37 - 10 = 27 lines

*/

