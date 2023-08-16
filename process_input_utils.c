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

/*Input: string to return an integer the number of "tokens" that can be 
created. A token is seperated by a space or tab, unless the space or tab 
is enclosed within matching double or single quotation marks. 

Any word that has no space or no tab and is next to the "outside" of a 
quotation mark: One token will be created to encompas the outside word 
and the whole quotation mark.*/
int	find_token_number(t_token **root)
{
	int		i;
	t_token	*curr;

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

// void	process_quotes(char *str, char type)
// {
// 	int	i;

// 	i = 0;
// 	i++;
// 	while (str[i] != type && str[i] != '\0')
// 		i++;
// 	if (str[i] == type)
// 		i++;
// }

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
		if (i == 0 && ft_is_pipe_or_redirect(str[i]) == 1)
		{
			i++;
			if (str[i] == str[i - 1])
			{
				i++;
			}
			break ;
		}
		if (ft_is_pipe_or_redirect(str[i]) == 1 || ft_white_space(str[i]) == 1)
			break ;
		if (ft_is_quote(str[i]) == 1)
		{
			type = str[i];
			i++;
			while (str[i] != type && str[i] != '\0')
				i++;
		}
		i++;
	}
	return (i);
}
