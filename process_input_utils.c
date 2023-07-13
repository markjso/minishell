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

extern	t_program	g_program;

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

/*Returns the index number of a string, the return value is the first space or 
tab to occur. Spaces within matching double or single quotation marks are 
ignored. The quotation is treated as one word. 

Any word that has no space or no tab and is next to the "outside" of a 
quotation mark: One token will be created to encompas the outside word 
and the whole quotation mark.*/
int	find_end(char *str)
{
	int			i;
	char		type;

	i = 0;
	while (str[i] != '\0')
	{
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
