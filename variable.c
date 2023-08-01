/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <jchurch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:47:33 by jchurch           #+#    #+#             */
/*   Updated: 2023/06/20 11:47:34 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// t_program g_program;

char	*ft_first_and_second(char *str, int *start, int env_start, int *end)
{
	char	*first;
	char	*second_temp;
	char	*second;
	char	*first_and_second;

	first = ft_substr(str, *start, env_start); // MALLOC freed
	second_temp = ft_substr(str, env_start, (*end) - env_start); // MALLOC freed
	second = ft_strdup(expand_dollar(second_temp)); // MALLOC freed
	free(second_temp); // FREE
	first_and_second = ft_strjoin(first, second); // MALLOC to be freed in parent function
	free(first); // FREE
	free(second); // FREE
	return (first_and_second);
}

void	dollar_found(t_token_list *curr, int *end, int *start)
{
	debugFunctionName("DOLLAR_FOUND");
	char	*first_and_second;
	int		env_start;
	char	*third_temp;
	char	*final;

	env_start = *end;
	while ((curr->data[*end] != '\0') && ft_is_not_white_space(curr->data[*end]) && ft_is_not_quote(curr->data[*end])) 
		(*end)++;
	first_and_second = ft_first_and_second(curr->data, start, env_start, end); // MALLOC freed
	*start = *end;
	while (curr->data[*end] != '\0')
		(*end)++;
	third_temp = ft_substr(curr->data, *start, *end - *start); // MALLOC freed
	final = ft_strjoin(first_and_second, third_temp); // MALLOC freed
	free(first_and_second); // FREE
	free(third_temp); // FREE
	replace_node_data(curr, final);
	free(final);
}

void	locate_dollar_for_action(t_token_list *curr)
{
	debugFunctionName("locate_dollar_for_action");
	int	end;
	int	start;

	end = 0;
	start = 0;
	while(curr->data[end] != '\0')
	{
		if (curr->data[end] == 39) // If is '. Skip over until next ' is found or end of string. 
		{
			skip_single_quote(curr->data, &end);
			continue ;
		}
		if (curr->data[end] == '$')  // If is $
		{
			dollar_found(curr, &end, &start);
			break ;
		}
		while (curr->data[end] != '\0' && curr->data[end] != '$' && curr->data[end] != 39) // Think of this as an else to the 2 ifs. 
			end++;
	}
}

int	count_dollars(char *str)
{
	debugFunctionName("COUNT_DOLLARS");
	int i;
	int	todo;

	i = 0;
	todo = 0;
	while(str[i] != '\0')
	{
		if (str[i] == 39) // If is '. Skip over until next ' is found or end of string. 
		{
			i++;
			while (str[i] != 39 && str[i] != '\0')
				i++;
		}
		if (str[i] == '$') // If is $
			todo++;
		i++;
	}
	return (todo);
}

void    expand_variables(t_token_list **root)
{
	debugFunctionName("EXPAND_TOKENS");
	t_token_list	*curr;
	int				todo;

	curr = *root;
	while (curr != NULL)
	{
		todo = count_dollars(curr->data);
		while (todo > 0)
		{
			locate_dollar_for_action(curr);
			todo--;
		}
		curr = curr->next;
	}
}